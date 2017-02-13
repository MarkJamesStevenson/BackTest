#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <string>

class DataProvider
{
public:
    DataProvider() = default;

    // This function should only be overriden
    // by backtesting data providers to pre-download
    // the required stock data before running.
    virtual void Initialise(std::string symbol) {}

    virtual void UpdateBars() = 0;
};

#endif // DATAPROVIDER_H
