#ifndef INTERACTIVEBROKERS_H
#define INTERACTIVEBROKERS_H

#include "broker.h"
#include "portfoliohandler.h"

class EventQueue;
class OrderEvent;

class InteractiveBrokers : public Broker
{
public:
    InteractiveBrokers(PortfolioHandler* portfolio) : portfolio(portfolio)
    {}

    void ExecuteOrder(const OrderEvent& event) override;

private:
    PortfolioHandler* portfolio;

    double CalculateCommission(const OrderEvent &event) const;

    double CalculateExchangeFees(const OrderEvent& event) const;
};

#endif // INTERACTIVEBROKERS_H
