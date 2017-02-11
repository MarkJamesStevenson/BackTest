#include "eventhandle.h"
#include <cassert>
#include "marketevent.h"

EventHandle::EventHandle(IEvent::Event_Type eventType)
{
    switch (eventType) {
        case IEvent::Event_Type::MARKET_EVENT :
            event.reset(new MarketEvent);
            break;
        default :
            assert(false && "You need to create a sub class of IEvent");
            break;
    }
}

IEvent::Event_Type EventHandle::GetEventType() const
{
    return event->GetEventType();
}

EventHandle::EventHandle(EventHandle &&rhs) :
    event(std::move(rhs.event))
{
}

EventHandle& EventHandle::operator=(EventHandle &&rhs)
{
    event.reset(std::move(rhs.event.release()));
    return *this;
}
