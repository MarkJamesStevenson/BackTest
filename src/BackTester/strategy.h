#ifndef STRATEGY_H
#define STRATEGY_H

#include <QObject>
class DataProvider;
class MarketEvent;

class Strategy : public QObject
{
    Q_OBJECT
public:   
    Strategy(DataProvider* dataProvider);

    virtual ~Strategy() = default;

public slots:
    virtual void ProcessMarketEvent(const MarketEvent& marketEvent) = 0;
};

#endif // STRATEGY_H
