#ifndef FILLEVENT_H
#define FILLEVENT_H

#include "ievent.h"
#include "memory"
/*
 * Event for when an order is filled, stores
 * the quantity filled and at what price.
 */


class FillEvent : public IEvent
{
public:
    template <typename Callable>
    FillEvent(const std::string& ticker,
              const std::string& exch,
              double volume,
              Direction side,
              double cost,
              Callable commissionCalculation) :
        IEvent(Event_Type::FILL_EVENT),
        symbol(ticker),
        exchange(exch),
        volumeFilled(volume),
        direction(side),
        fillCost(cost)
    {
        commission = commissionCalculation();
    }

    double getCommission() const
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
