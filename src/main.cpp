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
#include <QObject>

std::unique_ptr<DataProvider> CreateDataProvider(DataSource dataSource,
                                                 std::string symbol)
{
    std::unique_ptr<DataProvider> dataProvider = nullptr;
    try {
        DataProviderFactory dataProviderFactory;
        dataProvider = dataProviderFactory.CreateDataProvider(dataSource, symbol);
    } catch (const std::exception& e) {
        std::cerr << "Unable to continue as could not create data provider\n"
                  << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    return dataProvider;
}

void AssignListeners(Broker* broker, PortfolioHandler* portfolio, DataProvider* dataProvider, Strategy* strategy)
{
    dataProvider->AssignMarketEventListener(portfolio);
    dataProvider->AssignMarketEventListener(strategy);
    strategy->AssignSignalEventListener(portfolio);
    portfolio->AssignOrderEventListener(broker);
    broker->AssignFillEventListener(portfolio);
}

int main(int argc, char *argv[])
{
    auto dataProvider = CreateDataProvider(DataSource::YAHOOCSVDATAPROVIDER, "FDSA.L");
    if (dataProvider == nullptr)
    {
        std::cerr << "Unable to continue as could not create data provider\n";
        exit(EXIT_FAILURE);
    }
    PortfolioHandler portfolio;
    std::unique_ptr<Strategy> strategy(std::make_unique<BuyAndHoldStrategy>());
    std::unique_ptr<Broker> broker(std::make_unique<InteractiveBrokers>());
    AssignListeners(broker.get(), &portfolio, dataProvider.get(), strategy.get());
    while (dataProvider->DataAvailable())
    {
        dataProvider->UpdateBars();
        std::cout << "sleeping for 0.2 seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}

