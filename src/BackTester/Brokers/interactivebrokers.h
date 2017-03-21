#ifndef INTERACTIVEBROKERS_H
#define INTERACTIVEBROKERS_H

#include "broker.h"
#include "portfoliohandler.h"

class EventQueue;
class OrderEvent;

class InteractiveBrokers : public Broker
{
public:
    InteractiveBrokers() = default;

    void ProcessOrderEvent(const OrderEvent& event) override;

private:
    double CalculateCommission(const OrderEvent &event) const;

    double CalculateExchangeFees(const OrderEvent& event) const;
};

#endif // INTERACTIVEBROKERS_H
