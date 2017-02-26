#include "portfoliohandler.h"
#include "signalevent.h"
#include "marketevent.h"
#include "returntoidleevent.h"
#include "orderevent.h"
#include "fillevent.h"
#include "eventqueue.h"

#include <memory>
#include <iostream>


void PortfolioHandler::SignalUpdate(EventQueue &eventQueue, SignalEvent *signalEvent)
{
    if (signalEvent->GetSignalType() == Event::SignalType::LONG) {
        double capitalToSpend = volumePerTransaction * signalEvent->GetPrice();
        if (capitalToSpend <= capital) {
            // Just support market orders currently
            eventQueue.AddEvent(std::make_unique<OrderEvent>(signalEvent->GetSymbol(),
                                                             Event::OrderType::MKT,
                                                             volumePerTransaction,
                                                             Event::Direction::BUY));
        }
    } else if (signalEvent->GetSignalType() == Event::SignalType::SHORT){
        // We are selling so will always do the transaction
        eventQueue.AddEvent(std::make_unique<OrderEvent>(signalEvent->GetSymbol(),
                                                         Event::OrderType::MKT,
                                                         volumePerTransaction,
                                                         Event::Direction::SELL));
    } else if (signalEvent->GetSignalType() == Event::SignalType::EXIT) {
        if (volumeInvested > 0) {
            eventQueue.AddEvent(std::make_unique<OrderEvent>(signalEvent->GetSymbol(),
                                                             Event::OrderType::MKT,
                                                             volumeInvested,
                                                             Event::Direction::SELL));
        } else if (volumeInvested < 0) {
            eventQueue.AddEvent(std::make_unique<OrderEvent>(signalEvent->GetSymbol(),
                                                             Event::OrderType::MKT,
                                                             volumeInvested,
                                                             Event::Direction::BUY));
        }
    } else {
        std::cout << "Portfolio is taking no action" << std::endl;
        eventQueue.AddEvent(std::make_unique<ReturnToIdleEvent>());
    }
}

void PortfolioHandler::FillUpdate(EventQueue &eventQueue, FillEvent *fillEvent)
{

    std::cout << "Processed the fill now returning to idle" << std::endl;
    eventQueue.AddEvent(std::make_unique<ReturnToIdleEvent>());
}

void PortfolioHandler::MarketUpdate(MarketEvent *marketEvent)
{
    if (marketEvent)
    {
        // We presume the current price is the close price
        double lowPrice = marketEvent->GetClosePrice();
        capital = lowPrice * volumeInvested;
        std::cout << "Capital is now at " << capital << std::endl;
    }
}
