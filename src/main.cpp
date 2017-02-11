#include "BackTester/eventqueue.h"
#include "BackTester/ievent.h"
#include "BackTester/marketevent.h"
#include <iostream>

int main(int argc, char *argv[])
{
    EventQueue eventQueue;

    eventQueue.AddEvent(std::make_unique<MarketEvent>());
    if (!eventQueue.IsEmpty())
    {
        std::unique_ptr<IEvent> event = std::move(eventQueue.GetNextEvent());
        switch (event->getEventType()){
            case IEvent::Event_Type::MARKET_EVENT :
                std::cout << "market event" << std::endl;
                break;
            default :
                std::cout << "do not recognise the event type" << std::endl;
                break;
        }
    }
}

