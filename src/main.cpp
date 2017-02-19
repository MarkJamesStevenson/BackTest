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
#include "BackTester/transition.h"

int func()
{
    std::cout << "HI func" << std::endl;
    return 1;
}

int main(int argc, char *argv[])
{
    EventQueue eventQueue;
    YahooCSVDataProvider dataProvider;
    try {
        dataProvider.Initialise("GOOGL");
    } catch (const std::exception& e) {
        std::cout << "Unable to continue as could not initialise data provider\n"
                  << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    //Transition<decltype(func)> t(func);
    StateMachine stateMachine;
    while (dataProvider.DataAvailable())
    {
        dataProvider.UpdateBars(eventQueue);
        while (!eventQueue.IsEmpty())
        {
            std::unique_ptr<Event> event = eventQueue.GetNextEvent();
            if (event) {
                stateMachine.DoTransition(eventQueue, event->GetEventType());
            }
        }
        std::cout << "sleeping for 0.2 seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

