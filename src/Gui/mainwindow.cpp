#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "eventloop.h"
#include "marketevent.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupCandleStickGraph(ui->customPlot);
    setWindowTitle("QCustomPlot: ");
    statusBar()->clearMessage();
    ui->customPlot->replot();
    connect(ui->startEventLoop, SIGNAL (released()), this, SLOT (Run()));
}

void MainWindow::setupCandleStickGraph(QCustomPlot *customPlot)
{
  customPlot->legend->setVisible(true);

  // create candlestick chart:
  candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
  candlesticks->setName("Candlestick");
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
  dateTimeTicker->setDateTimeFormat("dd. MMMM yyyy");
  customPlot->xAxis->setTicker(dateTimeTicker);
  customPlot->rescaleAxes();
  customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());
  customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
  // make axis rects' left side line up:
  QCPMarginGroup *group = new QCPMarginGroup(customPlot);
  customPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
}

void MainWindow::ProcessMarketEvent(const MarketEvent &marketEvent)
{
    candlesticks->addData(marketEvent.GetDate().toTime_t(),
                          marketEvent.GetOpenPrice(),
                          marketEvent.GetHighPrice(),
                          marketEvent.GetLowPrice(),
                          marketEvent.GetClosePrice());
    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();
}

void MainWindow::Run()
{
    eventLoop.Run(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}
