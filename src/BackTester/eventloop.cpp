#include "eventloop.h"
#include "dataprovider.h"
#include "yahoocsvdataprovider.h"
#include <iostream>
#include <stdlib.h>
#include <memory>
#include <chrono>
#include <thread>
#include "strategy.h"
#include "buyandholdstrategy.h"
#include "portfoliohandler.h"
#include "broker.h"
#include "interactivebrokers.h"
#include "dataproviderfactory.h"
#include <QMainWindow>

void EventLoop::AssignListeners(QMainWindow* ui, Broker* broker, PortfolioHandler* portfolio, DataProvider* dataProvider, Strategy* strategy) const
{
    dataProvider->AssignMarketEventListener(ui);
    dataProvider->AssignMarketEventListener(portfolio);
    dataProvider->AssignMarketEventListener(strategy);
    broker->AssignFillEventListener(portfolio);
}

void EventLoop::Run(QMainWindow *ui) const
{
    std::unique_ptr<DataProvider> dataProvider = nullptr;
    try {
        DataProviderFactory dataProviderFactory;
        dataProvider = dataProviderFactory.CreateDataProvider(DataSource::YAHOOCSVFILEDATAPROVIDER, "MSFT.csv");
    } catch (const std::exception& e) {
        std::cerr << "Unable to continue as could not create data provider\n"
                  << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    std::shared_ptr<Broker> broker(std::make_shared<InteractiveBrokers>());
    std::shared_ptr<PortfolioHandler> portfolio(std::make_shared<PortfolioHandler>(broker));
    std::unique_ptr<Strategy> strategy(std::make_unique<BuyAndHoldStrategy>(portfolio));

    AssignListeners(ui, broker.get(), portfolio.get(), dataProvider.get(), strategy.get());
    while (dataProvider->DataAvailable())
    {
        dataProvider->UpdateBars();
        int milliseconds = 300;
        std::cout << "sleeping for " << milliseconds << " milliseconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
}

