#ifndef MARKETEVENT_H
#define MARKETEVENT_H

#include "event.h"
#include "ohlcdatapoint.h"
#include <iosfwd>
#include <QDateTime>

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

    double GetOpenPrice() const { return dataPoint.open; }

    double GetHighPrice() const { return dataPoint.high; }

    double GetLowPrice() const { return dataPoint.low; }

    double GetClosePrice() const { return dataPoint.adjClose; }

    QDateTime GetDate() const { return dataPoint.date; }

    std::string GetSymbol() const { return dataPoint.symbol; }

    friend std::ostream& operator<<(std::ostream& os, const MarketEvent& event);
private:
    OHLCDataPoint dataPoint;
};

std::ostream& operator<<(std::ostream& os, const MarketEvent& event);

#endif // MARKETEVENT_H
