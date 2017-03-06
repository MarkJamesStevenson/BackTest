#ifndef FILLEVENT_H
#define FILLEVENT_H

#include "event.h"
/*
 * Event for when an order is filled, stores
 * the quantity filled and at what price.
 */
class FillEvent : public Event
{
public:
    FillEvent(const std::string& symbol,
              const std::string& exch,
              int volume,
              Direction side,
              double cost,
              double commission) :
        Event(Event::EventType::FILL_EVENT),
        symbol(symbol),
        exchange(exch),
        volumeFilled(volume),
        direction(side),
        fillCost(cost),
        commission(commission)
    {
    }

    double GetCommission() const
    {
        return commission;
    }

    Direction GetDirection() const
    {
        return direction;
    }

    std::string GetSymbol() const
    {
        return symbol;
    }

    int GetVolumeFilled() const
    {
        return volumeFilled;
    }

    double GetFillCost() const
    {
        return fillCost;
    }

private:
    std::string symbol;
    std::string exchange;
    int volumeFilled;
    Direction direction;
    double fillCost;
    double commission;
};

#endif // FILLEVENT_H
