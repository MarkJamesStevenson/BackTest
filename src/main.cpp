#include "BackTester/eventqueue.h"
#include "BackTester/ievent.h"
#include "BackTester/marketevent.h"
#include <iostream>

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
            default :
                std::cout << "do not recognise the event type" << std::endl;
                break;
        }
    }
}

