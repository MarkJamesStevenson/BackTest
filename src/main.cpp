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

int main(int argc, char *argv[])
{
    EventQueue eventQueue;
    YahooCSVDataProvider dataProvider;
    try {
        dataProvider.Initialise("GOOGL");
    } catch (const std::exception& e) {
        std::cerr << "Unable to continue as could not initialise data provider\n"
                  << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    StateMachine stateMachine;
    std::unique_ptr<Strategy> strategy(std::make_unique<BuyAndHoldStrategy>());
    while (dataProvider.DataAvailable())
    {
        dataProvider.UpdateBars(eventQueue);
        while (!eventQueue.IsEmpty())
        {
            std::unique_ptr<Event> event = eventQueue.GetNextEvent();
            if (event) {
                stateMachine.DoTransition(eventQueue, event.get(), strategy.get());
            }
        }
        std::cout << "sleeping for 0.2 seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}

