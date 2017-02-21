#ifndef BUYANDHOLDSTRATEGY_H
#define BUYANDHOLDSTRATEGY_H

#include "strategy.h"

class BuyAndHoldStrategy : public Strategy
{
public:
    BuyAndHoldStrategy() = default;

    void ProcessDataUpdate(EventQueue& eventQueue, const OHLCDataPoint &dataPoint) override;

private:
    bool bought = false;
};

#endif // BUYANDHOLDSTRATEGY_H
