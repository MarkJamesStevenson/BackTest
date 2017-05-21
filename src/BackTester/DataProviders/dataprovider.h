#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <string>
#include <vector>
#include "ohlcdatapoint.h"
#include <QApplication>

class MarketEvent;
class EventQueue;

class DataProvider : public QObject
{
    Q_OBJECT
public:
    DataProvider() = default;

    virtual ~DataProvider() = default;

    // This function should be used to connect to data source
    // or retrieve any data required
    virtual void Initialise(const std::string& symbol) = 0;

    // This must be overridden and return true if there is
    // any more market data to be processed
    virtual bool DataAvailable() const = 0;

    // This must be overridden and it should emit a
    // PublishMarketEvent(const MarketEvent&).
    virtual void UpdateBars() = 0;

    template<typename T>
    void AssignMarketEventListener(T* listener)
    {
        QObject::connect(this, SIGNAL(PublishMarketEvent(const MarketEvent&)),
                         listener, SLOT(ProcessMarketEvent(const MarketEvent&)));
    }

    //Any class which needs market data can connect to this signal
signals:
    void PublishMarketEvent(const MarketEvent&);
};

#endif // DATAPROVIDER_H
