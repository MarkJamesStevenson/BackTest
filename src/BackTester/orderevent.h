#ifndef ORDEREVENT_H
#define ORDEREVENT_H

#include "ievent.h"
#include <string>

/*
 * Handles sending an order to a broker
 */
class OrderEvent : public IEvent
{
public: 

    OrderEvent(const std::string& ticker, OrderType type, double volume, Direction side) :
        IEvent(Event_Type::ORDER_EVENT),
        symbol(ticker),
        orderType(type),
        quantity(volume),
        direction(side)
    {}

    friend std::ostream& operator<<(std::ostream& os, const OrderEvent& event);

private:
    std::string symbol;
    OrderType orderType;
    double quantity;
    Direction direction;
};

std::ostream& operator<<(std::ostream& os, const OrderEvent& event);

#endif // ORDEREVENT_H
