#ifndef OHLCDATAPOINT_H
#define OHLCDATAPOINT_H

#include <string>

struct OHLCDataPoint {
    OHLCDataPoint(const std::string& symbol, const std::string& date, double open, double high, double low, double close, double volume, double adjClose)
        : symbol(symbol), date(date), open(open), high(high), low(low), close(close), volume(volume), adjClose(adjClose)
    {}

    const std::string symbol;
    const std::string date;
    double open;
    double high;
    double low;
    double close;
    double volume;
    double adjClose;
};

#endif // OHLCDATAPOINT_H
