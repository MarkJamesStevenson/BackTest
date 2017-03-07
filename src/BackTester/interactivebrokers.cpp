#include "interactivebrokers.h"
#include <algorithm>
#include "orderevent.h"
#include "fillevent.h"
#include "eventqueue.h"
#include <iostream>

void InteractiveBrokers::ExecuteOrder(EventQueue& eventQueue, OrderEvent *event)
{
    double totalCommision = CalculateCommission(event) + CalculateExchangeFees(event);
    std::cout << "Commission is " << totalCommision << std::endl;
    eventQueue.AddEvent(std::make_unique<FillEvent>(event->GetSymbol(),
                                                    "LSE",
                                                    event->GetVolume(),
                                                    event->GetDirection(),
                                                    event->GetVolume() * event->GetPricePerShare(),
                                                    totalCommision));
}

double InteractiveBrokers::CalculateCommission(OrderEvent* event) const
{
    if (event)
    {
        //This does not include exchange or ECN fees.
        //https://www.interactivebrokers.com/en/index.php?f=commission&p=stocks2
        double minCost = 100;
        return std::max(event->GetVolume() * event->GetPricePerShare() * 0.08 / 100, minCost);
    }
    return 0.0;
}

double InteractiveBrokers::CalculateExchangeFees(OrderEvent* event) const
{
    if (event) {
        // We assume we can only trade on LSE currently
        // https://www.interactivebrokers.com/en/index.php?f=commission&p=stocks2
        double minCost = 10;
        return std::max(event->GetVolume() * event->GetPricePerShare() * 0.45 / 100, minCost);
    }
    return 0.0;
}
