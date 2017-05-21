#ifndef OHLCDATAPOINT_H
#define OHLCDATAPOINT_H

#include <QDateTime>
#include <string>

struct OHLCDataPoint {
    OHLCDataPoint(const std::string& symbol, const QDateTime& date, double open, double high, double low, double close, double volume, double adjClose)
        : symbol(symbol), date(date), open(open), high(high), low(low), close(close), volume(volume), adjClose(adjClose)
    {}

    std::string symbol;
    QDateTime date;
    double open;
    double high;
    double low;
    double close;
    double volume;
    double adjClose;
};

#endif // OHLCDATAPOINT_H
