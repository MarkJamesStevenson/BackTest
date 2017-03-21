#ifndef INTERACTIVEBROKERS_H
#define INTERACTIVEBROKERS_H

#include "broker.h"
#include "portfoliohandler.h"

class OrderEvent;

class InteractiveBrokers : public Broker
{
public:
    InteractiveBrokers() = default;

public slots:
    void ProcessOrderEvent(const OrderEvent& event) override;

private:
    double CalculateCommission(const OrderEvent &event) const;

    double CalculateExchangeFees(const OrderEvent& event) const;
};

#endif // INTERACTIVEBROKERS_H
