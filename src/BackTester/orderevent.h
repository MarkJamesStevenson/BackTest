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

    OrderEvent(const std::string& ticker, OrderType type, double volume, Direction side) :
        symbol(ticker),
        orderType(type),
        quantity(volume),
        direction(side)
    {}

    void DoAction() {}

    friend std::ostream& operator<<(std::ostream& os, const OrderEvent& event);

private:
    std::string symbol;
    OrderType orderType;
    double quantity;
    Direction direction;
};

std::ostream& operator<<(std::ostream& os, const OrderEvent& event);

#endif // ORDEREVENT_H
