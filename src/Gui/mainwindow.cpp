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
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    setupCandleStickGraph(ui->customPlot);
    setWindowTitle("BackTest");
    statusBar()->clearMessage();
    errorMessage = new QErrorMessage(this);
    connect(ui->startEventLoop, &QPushButton::released, [=] () {
        Run();
    });
    connect(this, &MainWindow::ErrorMessage, [=] (const std::string& output){
        errorMessage->showMessage(QString::fromStdString(output));
    });
}

void MainWindow::setupCandleStickGraph(QCustomPlot *customPlot)
{
    customPlot->legend->setVisible(true);

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
    candlesticks->setName(QString::fromStdString(marketEvent.GetSymbol()));
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
    qRegisterMetaType<MarketEvent>();
    std::unique_ptr<DataProvider> dataProvider = nullptr;
    bool createdDataProvider = true;
    try {
        DataProviderFactory dataProviderFactory;
        dataProvider = dataProviderFactory.CreateDataProvider(DataSource::YAHOOCSVFILEDATAPROVIDER, "MSFT.csv");
    } catch (const std::exception& e) {
        std::cerr << "Unable to continue as could not create data provider\n"
                  << e.what() << "\n";
        std::string error("Unable to continue as could not create data provider. \n" + std::string(e.what()));
        emit ErrorMessage(error);
        createdDataProvider = false;
    }
    if (createdDataProvider) {
        std::shared_ptr<Broker> broker(std::make_shared<InteractiveBrokers>());
        std::shared_ptr<PortfolioHandler> portfolio(std::make_shared<PortfolioHandler>(broker));
        std::unique_ptr<Strategy> strategy(std::make_unique<BuyAndHoldStrategy>(portfolio));

        QThread* thread = new QThread(this);
        thread->start();
        EventLoop* eventLoop = new EventLoop();
        eventLoop->moveToThread(thread);
        broker->moveToThread(thread);
        portfolio->moveToThread(thread);
        dataProvider->moveToThread(thread);
        strategy->moveToThread(thread);
        AssignListeners(broker.get(), portfolio.get(), dataProvider.get(), strategy.get());
        connect(this, &MainWindow::RunLoop, [&] () {
            eventLoop->Run(dataProvider.get());
        });


        connect(thread, SIGNAL(destroyed()), eventLoop, SLOT(deleteLater()));
        emit RunLoop();
    }
}

void MainWindow::AssignListeners(Broker* broker, PortfolioHandler* portfolio, DataProvider* dataProvider, Strategy* strategy) const
{
    dataProvider->AssignMarketEventListener(this);
    dataProvider->AssignMarketEventListener(portfolio);
    dataProvider->AssignMarketEventListener(strategy);
    broker->AssignFillEventListener(portfolio);
}

MainWindow::~MainWindow()
{
    delete ui;
}
