#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <string>
#include <vector>
#include "ohlcdatapoint.h"
#include "eventqueue.h"

class DataProvider
{
public:
    DataProvider() = default;

    virtual ~DataProvider() = default;

    // This function should only be overriden
    // by backtesting data providers to pre-download
    // the required stock data before running.
    virtual void Initialise(const std::string& symbol) {}

    void UpdateBars(EventQueue& eventQueue);

    bool DataAvailable() const;

protected:
    std::vector<OHLCDataPoint> bars;
};

#endif // DATAPROVIDER_H
