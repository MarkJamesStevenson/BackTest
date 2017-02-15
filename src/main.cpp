#include "BackTester/eventqueue.h"
#include "BackTester/dataprovider.h"
#include "BackTester/yahoocsvdataprovider.h"
#include "BackTester/ievent.h"
#include "BackTester/marketevent.h"
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <memory>
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    EventQueue eventQueue;
    auto dataProvider(std::make_unique<YahooCSVDataProvider>());
    dataProvider->Initialise("FDSA.L");

    while (!dataProvider->IsEmpty())
    {
        dataProvider->UpdateBars(eventQueue);
        if (!eventQueue.IsEmpty())
        {
            std::unique_ptr<IEvent> event = eventQueue.GetNextEvent();
            if (event) {
                switch (event->GetEventType()){
                    case IEvent::Event_Type::MARKET_EVENT :
                        std::cout << *static_cast<MarketEvent*>(event.get()) << std::endl;
                        break;
                    case IEvent::Event_Type::FILL_EVENT :
                        std::cout << "fill event" << std::endl;
                        break;
                    case IEvent::Event_Type::ORDER_EVENT :
                        std::cout << "order event" << std::endl;
                        break;
                    case IEvent::Event_Type::SIGNAL_EVENT :
                        std::cout << "signal event" << std::endl;
                        break;
                    default :
                        assert(false && "Do not recognise the event type");
                        break;
                }
            }
        }
        std::cout << "sleeping for 2 seconds" << std::endl;
        std::this_thread::sleep_for (std::chrono::seconds(2));
    }
}

