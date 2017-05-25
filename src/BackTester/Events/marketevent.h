#ifndef MARKETEVENT_H
#define MARKETEVENT_H

#include "event.h"
#include "ohlcdatapoint.h"
#include <iosfwd>
#include <QDateTime>
#include <QMetaType>

/*
 * Creates the market event when new market data has
 * been received
 */
class MarketEvent
{
public:
    MarketEvent() : dataPoint("",QDateTime(),0,0,0,0,0,0)
    {}

    MarketEvent(const OHLCDataPoint& data) :
        dataPoint(data)
    {}

    MarketEvent(const MarketEvent& event) : dataPoint(event.dataPoint)
    {}

    ~MarketEvent() = default;

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
Q_DECLARE_METATYPE(MarketEvent);

std::ostream& operator<<(std::ostream& os, const MarketEvent& event);

#endif // MARKETEVENT_H
