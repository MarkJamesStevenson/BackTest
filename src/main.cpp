#include "BackTester/eventqueue.h"
#include "BackTester/dataprovider.h"
#include "BackTester/yahoocsvdataprovider.h"
#include "BackTester/event.h"
#include <iostream>
#include <stdlib.h>
#include <memory>
#include <chrono>
#include <thread>
#include "BackTester/statemachine.h"
#include "BackTester/strategy.h"
#include "BackTester/buyandholdstrategy.h"
#include "BackTester/portfoliohandler.h"
#include "BackTester/broker.h"
#include "BackTester/interactivebrokers.h"
#include "BackTester/dataproviderfactory.h"

std::unique_ptr<DataProvider> GetDataProvider(DataProviderFactory::DataSource dataSource,
                                              std::string symbol)
{
    std::unique_ptr<DataProvider> dataProvider = nullptr;
    try {
        DataProviderFactory dataProviderFactory;
        dataProvider = dataProviderFactory.GetDataProvider(dataSource, symbol);
    } catch (const std::exception& e) {
        std::cerr << "Unable to continue as could not create data provider\n"
                  << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    return dataProvider;
}

int main(int argc, char *argv[])
{
    EventQueue eventQueue;
    std::unique_ptr<DataProvider> dataProvider = GetDataProvider(
                DataProviderFactory::DataSource::YAHOOCSVDATAPROVIDER, "FDSA.L");
    StateMachine stateMachine;
    std::unique_ptr<Strategy> strategy(std::make_unique<BuyAndHoldStrategy>());
    std::unique_ptr<Broker> broker(std::make_unique<InteractiveBrokers>());
    PortfolioHandler portfolio;
    while (dataProvider->DataAvailable())
    {
        dataProvider->UpdateBars(eventQueue);
        while (!eventQueue.IsEmpty())
        {
            std::unique_ptr<Event> event = eventQueue.GetNextEvent();
            if (event) {
                stateMachine.DoTransition(eventQueue, event.get(), strategy.get(), portfolio, broker.get());
            }
        }
        std::cout << "sleeping for 0.2 seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

