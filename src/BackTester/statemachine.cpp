#include "statemachine.h"
#include <algorithm>
#include <iostream>
#include "returntoidleevent.h"
#include <cassert>
#include "marketevent.h"

void StateMachine::DoTransition(EventQueue &eventQueue, Event *event)
{
    if (event) {
        auto it = std::find_if(std::begin(stateTransitions), std::end(stateTransitions), [this, event] (const auto& transition) {
            return transition.currentState == currentState &&
                    transition.event == event->GetEventType();
        });
        if (it != std::end(stateTransitions)) {
            it->actionFunction(eventQueue, event);
            currentState = it->nextState;
        } else {
            assert(false && "Make sure you have added the transition to the stateTransitions table");
            std::cerr << "could not complete transition, remaining in current state" << std::endl;
        }
    }
}

void UpdateStrategyBars(EventQueue &eventQueue, Event* event)
{
    //At this stage we know that the event is a market event
    MarketEvent* marketEvent = static_cast<MarketEvent*>(event);
    // send the market event data to the strategy class to calculate
    eventQueue.AddEvent(std::make_unique<ReturnToIdleEvent>());
}

void ReturnToIdleState(EventQueue &eventQueue, Event* event)
{
    std::cout << "internal event\n\n";
}

void UpdatePortfolioBars(EventQueue &eventQueue, Event *event)
{

}

void SendOrderToBroker(EventQueue &eventQueue, Event* event)
{

}

void UpdatePortfolioFill(EventQueue &eventQueue, Event *event)
{

}
