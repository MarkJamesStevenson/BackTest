#ifndef STRATEGY_H
#define STRATEGY_H

#include <QObject>
class DataProvider;
class MarketEvent;
class PortfolioHandler;

class Strategy : public QObject
{
    Q_OBJECT
public:   
    Strategy(DataProvider* dataProvider, PortfolioHandler* portfolio);

    virtual ~Strategy() = default;

public slots:
    virtual void ProcessMarketEvent(const MarketEvent& marketEvent) = 0;

protected:
    PortfolioHandler* portfolio;
};

#endif // STRATEGY_H
