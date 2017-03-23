#include "portfoliohandler.h"
#include "signalevent.h"
#include "marketevent.h"
#include "orderevent.h"
#include "fillevent.h"
#include "dataprovider.h"

#include <memory>
#include <iostream>

void PortfolioHandler::ProcessFillEvent(const FillEvent& fillEvent)
{
    capital -= (fillEvent.GetFillCost() + fillEvent.GetCommission());
    if (fillEvent.GetDirection() == Event::Direction::BUY) {
        volumeInvested += fillEvent.GetVolumeFilled();
    } else {
        // Sold so we reduce volume invested
        volumeInvested -= fillEvent.GetVolumeFilled();
    }
    std::cout << "Processed the fill event" << std::endl;
}

void PortfolioHandler::ProcessMarketEvent(const MarketEvent& marketEvent)
{
    // We presume the current price is the close price
    double closePrice = marketEvent.GetClosePrice();
    capitalInvested = closePrice * volumeInvested;
    std::cout << "Date: " << marketEvent.GetDate() << "\n"
              << "Share price is: " << marketEvent.GetClosePrice() << "\n"
              << "Capital Invested is now at: " << capitalInvested << "\n"
              << "Remaining capital is: " << capital << "\n"
              << "Total capital is " << capitalInvested + capital << std::endl;
}

void PortfolioHandler::BuyOrderRequest(const SignalEvent &signalEvent)
{
    double capitalToSpend = volumePerTransaction * signalEvent.GetPrice();
    std::cout << "the amount strategy wants to spend is " << capitalToSpend << std::endl;
    std::cout << "the amount of capital available is " << capital << std::endl;
    if (capitalToSpend <= capital) {
        // Just support market orders currently
        broker->ProcessOrderEvent({signalEvent.GetSymbol(),
                                   Event::OrderType::MKT,
                                   volumePerTransaction,
                                   signalEvent.GetPrice(),
                                   Event::Direction::BUY});
    } else {
        std::cout << "Portfolio is taking no long action" << std::endl;
    }
}

void PortfolioHandler::SellOrderRequest(const SignalEvent &signalEvent)
{
    // We are selling so will always do the transaction
    broker->ProcessOrderEvent({signalEvent.GetSymbol(),
                               Event::OrderType::MKT,
                               volumePerTransaction,
                               signalEvent.GetPrice(),
                               Event::Direction::SELL});
}

void PortfolioHandler::ExitOrderRequest(const SignalEvent &signalEvent)
{
    if (volumeInvested > 0) {
        broker->ProcessOrderEvent({signalEvent.GetSymbol(),
                                   Event::OrderType::MKT,
                                   volumeInvested,
                                   signalEvent.GetPrice(),
                                   Event::Direction::SELL});
    } else if (volumeInvested < 0) {
        broker->ProcessOrderEvent({signalEvent.GetSymbol(),
                                   Event::OrderType::MKT,
                                   volumeInvested,
                                   signalEvent.GetPrice(),
                                   Event::Direction::BUY});
    } else {
        std::cout << "Portfolio is taking no action as no volume invested" << std::endl;
    }
}
