#ifndef BUYANDHOLDSTRATEGY_H
#define BUYANDHOLDSTRATEGY_H

#include "strategy.h"
#include <memory>
class MarketEvent;
class DataProvider;

class BuyAndHoldStrategy : public Strategy
{
public:
    BuyAndHoldStrategy(const std::shared_ptr<PortfolioHandler>& portfolio) :
        Strategy(portfolio)
    {}

    void ProcessMarketEvent(const MarketEvent& marketEvent) override;

private:
    bool bought = false;
};

#endif // BUYANDHOLDSTRATEGY_H
