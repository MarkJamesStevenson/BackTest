#ifndef MARKETEVENT_H
#define MARKETEVENT_H

#include "event.h"
#include "ohlcdatapoint.h"
#include <iostream>

/*
 * Creates the market event when new market data has
 * been received
 */
class MarketEvent : public Event
{
public:
    MarketEvent(const OHLCDataPoint& data) :
        Event(Event::EventType::MARKET_EVENT),
        dataPoint(data)
    {}

    friend std::ostream& operator<<(std::ostream& os, const MarketEvent& event);
private:
    OHLCDataPoint dataPoint;
};

std::ostream& operator<<(std::ostream& os, const MarketEvent& event);

#endif // MARKETEVENT_H
