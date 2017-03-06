#ifndef INTERACTIVEBROKERS_H
#define INTERACTIVEBROKERS_H

#include "broker.h"

class EventQueue;
class OrderEvent;

class InteractiveBrokers : public Broker
{
public:
    InteractiveBrokers() = default;

    void ExecuteOrder(EventQueue &eventQueue, OrderEvent* event) override;
private:
    double CalculateCommission(OrderEvent *event) const;

    double CalculateExchangeFees(OrderEvent* event) const;
};

#endif // INTERACTIVEBROKERS_H
