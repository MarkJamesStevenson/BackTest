#include "BackTester/eventqueue.h"
#include "BackTester/ievent.h"
#include "BackTester/marketevent.h"
#include <iostream>
#include <cassert>

int main(int argc, char *argv[])
{
    EventQueue eventQueue;
    eventQueue.AddEvent(EventHandle(IEvent::Event_Type::MARKET_EVENT));
    if (!eventQueue.IsEmpty())
    {
        EventHandle event = eventQueue.GetNextEvent();
        switch (event.GetEventType()){
            case IEvent::Event_Type::MARKET_EVENT :
                std::cout << "market event" << std::endl;
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
                assert(false && "You need to add the event type here");
                break;
        }
    }
}

