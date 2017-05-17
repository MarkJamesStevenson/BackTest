#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <string>
#include <vector>
#include "ohlcdatapoint.h"
#include <QApplication.h>

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

    bool DataAvailable() const;

    void UpdateBars();

    template<typename T>
    void AssignMarketEventListener(T* listener)
    {
        QObject::connect(this, SIGNAL(PublishMarketEvent(const MarketEvent&)),
                         listener, SLOT(ProcessMarketEvent(const MarketEvent&)));
    }

    //Any class which needs market data can connect to this signal
signals:
    void PublishMarketEvent(const MarketEvent&);

protected:
    std::vector<OHLCDataPoint> bars;
};

#endif // DATAPROVIDER_H
