#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupFinancialDemo(ui->customPlot);
    setWindowTitle("QCustomPlot: ");
    statusBar()->clearMessage();
    ui->customPlot->replot();
}

void MainWindow::setupFinancialDemo(QCustomPlot *customPlot)
{
  customPlot->legend->setVisible(true);

  // generate two sets of random walk data (one for candlestick and one for ohlc chart):
  int n = 500;
  QVector<double> time(n), value1(n), value2(n);
  QDateTime start = QDateTime(QDate(2014, 6, 11));
  start.setTimeSpec(Qt::UTC);
  double startTime = start.toTime_t();
  double binSize = 3600*24; // bin data in 1 day intervals
  time[0] = startTime;
  value1[0] = 60;
  value2[0] = 20;
  qsrand(9);
  for (int i=1; i<n; ++i)
  {
    time[i] = startTime + 3600*i;
    value1[i] = value1[i-1] + (qrand()/(double)RAND_MAX-0.5)*10;
    value2[i] = value2[i-1] + (qrand()/(double)RAND_MAX-0.5)*3;
  }

  // create candlestick chart:
  QCPFinancial *candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
  candlesticks->setName("Candlestick");
  candlesticks->setChartStyle(QCPFinancial::csCandlestick);
  candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(time, value1, binSize, startTime));
  candlesticks->setWidth(binSize*0.9);
  candlesticks->setTwoColored(true);
  candlesticks->setBrushPositive(QColor(245, 245, 245));
  candlesticks->setBrushNegative(QColor(40, 40, 40));
  candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
  candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));

  // create bottom axis rect for volume bar chart:
  QCPAxisRect *volumeAxisRect = new QCPAxisRect(customPlot);
  customPlot->plotLayout()->addElement(1, 0, volumeAxisRect);
  volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
  volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
  volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
  // bring bottom and main axis rect closer together:
  customPlot->plotLayout()->setRowSpacing(0);
  volumeAxisRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
  volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
  // create two bar plottables, for positive (green) and negative (red) volume bars:
  customPlot->setAutoAddPlottableToLegend(false);
  QCPBars *volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
  QCPBars *volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
  for (int i=0; i<n/5; ++i)
  {
    int v = qrand()%20000+qrand()%20000+qrand()%20000-10000*3;
    (v < 0 ? volumeNeg : volumePos)->addData(startTime+3600*5.0*i, qAbs(v)); // add data to either volumeNeg or volumePos, depending on sign of v
  }
  volumePos->setWidth(3600*4);
  volumePos->setPen(Qt::NoPen);
  volumePos->setBrush(QColor(100, 180, 110));
  volumeNeg->setWidth(3600*4);
  volumeNeg->setPen(Qt::NoPen);
  volumeNeg->setBrush(QColor(180, 90, 90));

  // interconnect x axis ranges of main and bottom axis rects:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
  connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis, SLOT(setRange(QCPRange)));
  // configure axes of both main and bottom axis rect:
  QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
  dateTimeTicker->setDateTimeSpec(Qt::UTC);
  dateTimeTicker->setDateTimeFormat("dd. MMMM");
  volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
  volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
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
  volumeAxisRect->setMarginGroup(QCP::msLeft|QCP::msRight, group);
}


MainWindow::~MainWindow()
{
    delete ui;
}
