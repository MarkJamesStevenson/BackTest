#ifndef BUYANDHOLDSTRATEGY_H
#define BUYANDHOLDSTRATEGY_H

#include "strategy.h"
class MarketEvent;

class BuyAndHoldStrategy : public Strategy
{
public:
    BuyAndHoldStrategy() = default;

    void ProcessDataUpdate(EventQueue& eventQueue, MarketEvent* marketEvent) override;

private:
    bool bought = false;
};

#endif // BUYANDHOLDSTRATEGY_H
