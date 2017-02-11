#ifndef MARKETEVENT_H
#define MARKETEVENT_H

#include "ievent.h"

/*
 * Creates the market event when new market data has
 * been received
 */
class MarketEvent : public IEvent
{
public:
    MarketEvent() : IEvent(Event_Type::MARKET_EVENT) {}
};

#endif // MARKETEVENT_H
