#ifndef MARKETEVENT_H
#define MARKETEVENT_H

#include "ievent.h"

class MarketEvent : public IEvent
{
public:
    MarketEvent() : IEvent(Event_Type::MARKET_EVENT) {}
};

#endif // MARKETEVENT_H
