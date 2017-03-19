#include "buyandholdstrategy.h"
#include "signalevent.h"
#include "marketevent.h"
#include <iostream>

void BuyAndHoldStrategy::ProcessMarketEvent(const MarketEvent &marketEvent)
{
    if (!bought) {
        bought = true;
        std::cout << "strategy has decided to buy" << std::endl;
        //eventQueue.AddEvent(std::make_unique<SignalEvent>("GOOGL", Event::SignalType::LONG, marketEvent->GetClosePrice()));
    } else {
        std::cout << "strategy has decided to not do any work \n\n";
    }
}
