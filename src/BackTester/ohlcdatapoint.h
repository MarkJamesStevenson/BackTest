#ifndef OHLCDATAPOINT_H
#define OHLCDATAPOINT_H

#include <string>

struct OHLCDataPoint {
    OHLCDataPoint(const std::string& date, double open, double high, double low, double close, double volume, double adjClose)
        : date(date), open(open), high(high), low(low), close(close), volume(volume), adjClose(adjClose)
    {}

    std::string date;
    double open;
    double high;
    double low;
    double close;
    double volume;
    double adjClose;
};

#endif // OHLCDATAPOINT_H
