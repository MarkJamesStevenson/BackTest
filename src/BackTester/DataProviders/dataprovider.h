#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <string>
#include <vector>
#include "ohlcdatapoint.h"
#include <QObject>

class MarketEvent;
class EventQueue;

class DataProvider : public QObject
{
    Q_OBJECT
public:
    DataProvider() = default;

    virtual ~DataProvider() = default;

    // This function should only be overriden
    // by backtesting data providers to pre-download
    // the required stock data before running.
    virtual void Initialise(const std::string& symbol) {}

    bool DataAvailable() const;

    void UpdateBars();

    //Any class which needs market data can connect to this signal
signals:
    virtual void PublishMarketEvent(const MarketEvent&);

protected:
    std::vector<OHLCDataPoint> bars;
};

#endif // DATAPROVIDER_H
