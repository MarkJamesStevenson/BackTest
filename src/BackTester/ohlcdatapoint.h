#ifndef OHLCDATAPOINT_H
#define OHLCDATAPOINT_H

#include <string>

struct OHLCDataPoint {
    OHLCDataPoint(const std::string& date, int open, int high, int low, int close, int volume, int adjClose)
        : date(date), open(open), high(high), low(low), close(close), volume(volume), adjClose(adjClose)
    {}

    std::string date;
    int open;
    int high;
    int low;
    int close;
    int volume;
    int adjClose;
};

#endif // OHLCDATAPOINT_H
