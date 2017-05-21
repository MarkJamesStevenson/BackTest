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
  int n = 500;
  QVector<double> time(n), value1(n), value2(n);
  start = QDateTime(QDate(2014, 6, 11));
  start.setTimeSpec(Qt::UTC);
  double startTime = start.toTime_t();
  double binSize = 3600*24; // bin data in 1 day intervals
  time[0] = startTime;
  value1[0] = 70;
  value2[0] = 20;
  qsrand(9);
  for (int i=1; i<n; ++i)
  {

    time[i] = startTime + 3600*i;
    value1[i] = value1[i-1] + (qrand()/(double)RAND_MAX-0.5)*10;
    value2[i] = value2[i-1] + (qrand()/(double)RAND_MAX-0.5)*3;
  }

  // create candlestick chart:
  candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
  candlesticks->setName("Candlestick");
  candlesticks->setChartStyle(QCPFinancial::csCandlestick);
  /*candlesticks->addData(startTime, 31.2188,
                        33.0625,
                        31,
                        32.375);*/
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
    static int i = 1;
    double time = start.toTime_t() + 3600 * 24 * i;
    i++;
    std::cout << marketEvent.GetOpenPrice() << std::endl;
    std::cout << marketEvent.GetHighPrice() << std::endl;
    std::cout << marketEvent.GetLowPrice() << std::endl;
    std::cout << marketEvent.GetClosePrice() << std::endl;

    candlesticks->addData(time,
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
