#ifndef FILLEVENT_H
#define FILLEVENT_H

#include "event.h"
/*
 * Event for when an order is filled, stores
 * the quantity filled and at what price.
 * TODO : decide the best way to handle commission charges
 * may be best to have a IBroker class.
 */
class FillEvent : public Event
{
public:
    template <typename Callable>
    FillEvent(const std::string& ticker,
              const std::string& exch,
              double volume,
              Direction side,
              double cost,
              Callable commissionCalculation) :
        symbol(ticker),
        exchange(exch),
        volumeFilled(volume),
        direction(side),
        fillCost(cost)
    {
        commission = commissionCalculation();
    }

    void DoAction() {}

    double GetCommission() const
    {
        return commission;
    }

private:
    std::string symbol;
    std::string exchange;
    double volumeFilled;
    Direction direction;
    double fillCost;
    double commission;
};

#endif // FILLEVENT_H
