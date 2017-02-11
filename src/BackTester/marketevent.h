#ifndef MARKETEVENT_H
#define MARKETEVENT_H

#include "ievent.h"

class MarketEvent : public IEvent
{
public:
    MarketEvent() = default;

    virtual Event_Type getEventType()
    {
        return event;
    }

private:
    Event_Type event = Event_Type::MARKET_EVENT;
};

#endif // MARKETEVENT_H
