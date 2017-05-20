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
  start.setTimeSpec(Qt::UTC);
  double startTime = start.toTime_t();

  // create candlestick chart:
  candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
  candlesticks->setName("Candlestick");
  candlesticks->setChartStyle(QCPFinancial::csCandlestick);
  candlesticks->setWidth(binSize*0.9);
  candlesticks->setTwoColored(true);
  candlesticks->setBrushPositive(QColor(245, 245, 245));
  candlesticks->setBrushNegative(QColor(40, 40, 40));
  candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
  candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));

  // configure axes of both main and bottom axis rect:
  QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
  dateTimeTicker->setDateTimeSpec(Qt::UTC);
  dateTimeTicker->setDateTimeFormat("dd. MMMM");
  customPlot->xAxis->setBasePen(Qt::NoPen);
  customPlot->xAxis->setTickLabels(false);
  customPlot->xAxis->setTicks(false); // only want vertical grid in main axis rect, so hide xAxis backbone, ticks, and labels
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
    std::cout << "processing market event in the ui \n\n";
    start.addDays(1);
    candlesticks->addData(start.toTime_t(),
                          marketEvent.GetOpenPrice(),
                          marketEvent.GetHighPrice(),
                          marketEvent.GetLowPrice(),
                          marketEvent.GetClosePrice());
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
