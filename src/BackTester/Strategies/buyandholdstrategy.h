#ifndef BUYANDHOLDSTRATEGY_H
#define BUYANDHOLDSTRATEGY_H

#include "strategy.h"
class MarketEvent;
class DataProvider;

class BuyAndHoldStrategy : public Strategy
{
public:
    BuyAndHoldStrategy(DataProvider* dataProvider, PortfolioHandler* portfolio)
        : Strategy(dataProvider, portfolio) {}

    void ProcessMarketEvent(const MarketEvent& marketEvent) override;
private:
    bool bought = false;
};

#endif // BUYANDHOLDSTRATEGY_H
