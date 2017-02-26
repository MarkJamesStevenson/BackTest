#include "buyandholdstrategy.h"
#include "returntoidleevent.h"
#include "signalevent.h"
#include <iostream>

void BuyAndHoldStrategy::ProcessDataUpdate(EventQueue &eventQueue, MarketEvent *marketEvent)
{
    if (!bought) {
        bought = true;
        std::cout << "strategy has decided to buy" << std::endl;
        eventQueue.AddEvent(std::make_unique<SignalEvent>("GOOGL", Event::SignalType::LONG, marketEvent->GetClosePrice()));
    } else {
        std::cout << "strategy has decided to return to idle \n\n";
        eventQueue.AddEvent(std::make_unique<ReturnToIdleEvent>());
    }
}
