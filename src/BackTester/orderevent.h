#ifndef ORDEREVENT_H
#define ORDEREVENT_H

#include "event.h"
#include <string>

/*
 * Handles sending an order to a broker
 */
class OrderEvent : public Event
{
public: 

    OrderEvent(const std::string& ticker, OrderType type, int volume, double pricePerShare, Direction side) :
        Event(Event::EventType::ORDER_EVENT),
        symbol(ticker),
        orderType(type),
        volume(volume),
        pricePerShare(pricePerShare),
        direction(side)
    {}

    std::string GetSymbol() const
    {
        return symbol;
    }

    double GetPricePerShare() const
    {
        return pricePerShare;
    }

    int GetVolume() const
    {
        return volume;
    }

    Direction GetDirection() const
    {
        return direction;
    }

    friend std::ostream& operator<<(std::ostream& os, const OrderEvent& event);

private:
    std::string symbol;
    OrderType orderType;
    int volume;
    double pricePerShare;
    Direction direction;
};

std::ostream& operator<<(std::ostream& os, const OrderEvent& event);

#endif // ORDEREVENT_H
