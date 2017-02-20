#include "statemachine.h"
#include <algorithm>
#include <iostream>
#include "returntoidleevent.h"
#include <cassert>
#include "marketevent.h"

// This array contains all the possible state transitions. The action is a function pointer which implements the
// functionality for the new state.
const std::array<StateMachine::Transition, 6> StateMachine::stateTransitions = {{
    //CURRENT STATE                               EVENT                              NEXT STATE                                  ACTION
    { StateMachine::State::IDLE,                  Event::EventType::MARKET_EVENT,    StateMachine::State::STRATEGY_CALCULATION,  &UpdateStrategyBars },
    { StateMachine::State::STRATEGY_CALCULATION,  Event::EventType::SIGNAL_EVENT,    StateMachine::State::PORTFOLIO_CALCULATION, &UpdatePortfolioBars },
    { StateMachine::State::STRATEGY_CALCULATION,  Event::EventType::RETURN_TO_IDLE,  StateMachine::State::IDLE,                  &ReturnToIdleState },
    { StateMachine::State::PORTFOLIO_CALCULATION, Event::EventType::ORDER_EVENT,     StateMachine::State::ORDER_ENTRY,           &SendOrderToBroker },
    { StateMachine::State::ORDER_ENTRY,           Event::EventType::FILL_EVENT,      StateMachine::State::PORTFOLIO_CALCULATION, &UpdatePortfolioFill },
    { StateMachine::State::PORTFOLIO_CALCULATION, Event::EventType::RETURN_TO_IDLE,  StateMachine::State::IDLE,                  &ReturnToIdleState }
}};

void StateMachine::DoTransition(EventQueue &eventQueue, Event *event)
{
    if (event) {
        auto it = std::find_if(std::cbegin(stateTransitions), std::cend(stateTransitions), [this, event] (const auto& transition) {
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
    //At this stage the event should always be a market event
    MarketEvent* marketEvent = dynamic_cast<MarketEvent*>(event);
    if (marketEvent) {
        std::cout << "strategy has decided to return to idle \n\n";
        // send the market event data to the strategy class to calculate
        eventQueue.AddEvent(std::make_unique<ReturnToIdleEvent>());
    } else {
        assert(false && "should only be market events here");
    }
}

void ReturnToIdleState(EventQueue &eventQueue, Event* event)
{
    std::cout << "Returning to state IDLE" << std::endl;
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
