#include "buyandholdstrategy.h"
#include "signalevent.h"
#include "marketevent.h"
#include <iostream>
#include "portfoliohandler.h"

void BuyAndHoldStrategy::ProcessMarketEvent(const MarketEvent &marketEvent)
{
    if (!bought) {
        bought = true;
        std::cout << "strategy has decided to buy" << std::endl;
        emit PublishBuySignalEvent(SignalEvent(marketEvent.GetSymbol(),
                                               Event::SignalType::LONG,
                                               marketEvent.GetClosePrice()));
    } else {
        std::cout << "strategy has decided to not do any work \n\n";
    }
}
