#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventloop.h"
#include "marketevent.h"
#include <iostream>
#include <thread>
#include <functional>
#include "dataproviderfactory.h"
#include <memory>
#include "interactivebrokers.h"
#include "buyandholdstrategy.h"
#include <QErrorMessage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    errorMessage(new QErrorMessage(this))
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    setupCandleStickGraph(ui->customPlot);
    setWindowTitle("BackTest");
    statusBar()->clearMessage();
    connect(ui->startEventLoop, &QPushButton::released, [this] () {
        Run();
    });
}

void MainWindow::setupCandleStickGraph(QCustomPlot *customPlot)
{
    customPlot->legend->setVisible(true);
    customPlot->setInteraction(QCP::iRangeZoom, true);
    customPlot->setSelectionRectMode(QCP::srmZoom);
    candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    double binSize = 3600*24; // bin data in 1 day intervals
    candlesticks->setWidth(binSize*0.9);
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(100, 180, 110));
    candlesticks->setBrushNegative(QColor(180, 90, 90));
    candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
    candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));

    // configure axes of both main and bottom axis rect:
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd MMMM yy");
    customPlot->xAxis->setTicker(dateTimeTicker);
    customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());
    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
    // make axis rects' left side line up:
    QCPMarginGroup *group = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
}

void MainWindow::ProcessMarketEvent(const MarketEvent &marketEvent)
{
    static int count = 0;
    candlesticks->addData(marketEvent.GetDate().toTime_t(),
                          marketEvent.GetOpenPrice(),
                          marketEvent.GetHighPrice(),
                          marketEvent.GetLowPrice(),
                          marketEvent.GetClosePrice());
    if (count % 100 == 0)
    {
        candlesticks->setName(QString::fromStdString(marketEvent.GetSymbol()));
        UpdateCandlesticks();
        count = 0;
    }
    count++;
}

void MainWindow::UpdateCandlesticks()
{
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}

void MainWindow::Run()
{
    candlesticks->setData({},{},{},{},{},true);
    qRegisterMetaType<MarketEvent>();
    workerThread = new QThread();
    eventLoop = new EventLoop();
    eventLoop->moveToThread(workerThread);
    connect(workerThread, &QThread::started, [this] ()
    {
        eventLoop->Run(this);
    });
    connect(eventLoop, SIGNAL(ErrorMessage(const QString&)), this, SLOT(DisplayErrorMessage(const QString&)));
    connect(eventLoop, SIGNAL(EventLoopCompleted()), this, SLOT(UpdateCandlesticks()));
    connect(eventLoop, SIGNAL(EventLoopCompleted()), workerThread, SLOT(quit()));
    connect(eventLoop, &EventLoop::EventLoopCompleted, [this] ()
    {
       delete eventLoop;
    });
    workerThread->start();
}

void MainWindow::DisplayErrorMessage(const QString& error)
{
    errorMessage->showMessage(error);
}

MainWindow::~MainWindow()
{
    delete ui;
}
