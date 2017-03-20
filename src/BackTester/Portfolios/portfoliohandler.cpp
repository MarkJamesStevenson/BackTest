#include "portfoliohandler.h"
#include "signalevent.h"
#include "marketevent.h"
#include "orderevent.h"
#include "fillevent.h"
#include "dataprovider.h"

#include <memory>
#include <iostream>

PortfolioHandler::PortfolioHandler(DataProvider *dataProvider, double initialCapital, int volumePerTransaction) :
    capital(initialCapital),
    volumePerTransaction(volumePerTransaction),
    volumeInvested(0),
    capitalInvested(0.0)
{
    QObject::connect(dataProvider, SIGNAL(PublishMarketEvent(const MarketEvent&)),
                     this, SLOT(ProcessMarketEvent(const MarketEvent&)));
}

void PortfolioHandler::OrderRequest(const SignalEvent& signalEvent)
{
    if (signalEvent.GetSignalType() == Event::SignalType::LONG) {
        double capitalToSpend = volumePerTransaction * signalEvent.GetPrice();
        std::cout << "the amount strategy wants to spend is " << capitalToSpend << std::endl;
        std::cout << "the amount of capital available is " << capital << std::endl;
        if (capitalToSpend <= capital) {
            // Just support market orders currently
            /*eventQueue.AddEvent(std::make_unique<OrderEvent>(signalEvent->GetSymbol(),
                                                             Event::OrderType::MKT,
                                                             volumePerTransaction,
                                                             signalEvent->GetPrice(),
                                                             Event::Direction::BUY));*/
        } else {
            std::cout << "Portfolio is taking no long action" << std::endl;
        }
    } else if (signalEvent.GetSignalType() == Event::SignalType::SHORT){
        // We are selling so will always do the transaction
        /*eventQueue.AddEvent(std::make_unique<OrderEvent>(signalEvent->GetSymbol(),
                                                         Event::OrderType::MKT,
                                                         volumePerTransaction,
                                                         signalEvent->GetPrice(),
                                                         Event::Direction::SELL));*/
    } else if (signalEvent.GetSignalType() == Event::SignalType::EXIT) {
        if (volumeInvested > 0) {
            /*eventQueue.AddEvent(std::make_unique<OrderEvent>(signalEvent->GetSymbol(),
                                                             Event::OrderType::MKT,
                                                             volumeInvested,
                                                             signalEvent->GetPrice(),
                                                             Event::Direction::SELL));*/
        } else if (volumeInvested < 0) {
            /*eventQueue.AddEvent(std::make_unique<OrderEvent>(signalEvent->GetSymbol(),
                                                             Event::OrderType::MKT,
                                                             volumeInvested,
                                                             signalEvent->GetPrice(),
                                                             Event::Direction::BUY));*/
        } else {
            std::cout << "Portfolio is taking no action as no volume invested" << std::endl;
        }
    } else {
        std::cout << "Portfolio is taking no action" << std::endl;
    }
}

void PortfolioHandler::FillUpdate(const FillEvent &fillEvent)
{
    capital -= fillEvent.GetFillCost() + fillEvent.GetCommission();
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
