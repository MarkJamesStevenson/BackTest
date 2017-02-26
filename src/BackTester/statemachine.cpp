#include "statemachine.h"
#include <algorithm>
#include <iostream>
#include "returntoidleevent.h"
#include <cassert>
#include "marketevent.h"
#include "signalevent.h"
#include "fillevent.h"
#include "strategy.h"
#include "portfoliohandler.h"

// This array contains all the possible state transitions. The action is a function pointer which implements the
// functionality for the new state.
const std::array<StateMachine::Transition, 6> StateMachine::stateTransitions = {{
    //CURRENT STATE                               EVENT                              NEXT STATE                                  ACTION
    { StateMachine::State::IDLE,                  Event::EventType::MARKET_EVENT,    StateMachine::State::STRATEGY_CALCULATION,  &UpdateStrategyBars },
    { StateMachine::State::STRATEGY_CALCULATION,  Event::EventType::SIGNAL_EVENT,    StateMachine::State::PORTFOLIO_CALCULATION, &UpdatePortfolioSignal },
    { StateMachine::State::STRATEGY_CALCULATION,  Event::EventType::RETURN_TO_IDLE,  StateMachine::State::IDLE,                  &ReturnToIdleState },
    { StateMachine::State::PORTFOLIO_CALCULATION, Event::EventType::ORDER_EVENT,     StateMachine::State::ORDER_ENTRY,           &SendOrderToBroker },
    { StateMachine::State::ORDER_ENTRY,           Event::EventType::FILL_EVENT,      StateMachine::State::PORTFOLIO_CALCULATION, &UpdatePortfolioFill },
    { StateMachine::State::PORTFOLIO_CALCULATION, Event::EventType::RETURN_TO_IDLE,  StateMachine::State::IDLE,                  &ReturnToIdleState }
}};

void StateMachine::DoTransition(EventQueue &eventQueue, Event *event, Strategy* strategy, PortfolioHandler& portfolio)
{
    if (event && strategy) {
        auto it = std::find_if(std::cbegin(stateTransitions), std::cend(stateTransitions), [this, event] (const auto& transition) {
            return transition.currentState == currentState &&
                   transition.event == event->GetEventType();
        });
        if (it != std::cend(stateTransitions)) {
            it->actionFunction(eventQueue, event, strategy, portfolio);
            currentState = it->nextState;
        } else {
            assert(false && "Make sure you have added the transition to the stateTransitions table");
            std::cerr << "Could not complete transition, remaining in current state" << std::endl;
        }
    }
}

void UpdateStrategyBars(EventQueue &eventQueue, Event* event, Strategy *strategy, PortfolioHandler &portfolio)
{
    //At this stage the event should always be a market event
    MarketEvent* marketEvent = dynamic_cast<MarketEvent*>(event);
    if (marketEvent) {
        strategy->ProcessDataUpdate(eventQueue, marketEvent);
        portfolio.MarketUpdate(marketEvent);
    } else {
        assert(false && "should only be market events here");
    }
}

void ReturnToIdleState(EventQueue &eventQueue, Event* event, Strategy *strategy, PortfolioHandler &portfolio)
{
    std::cout << "Returning to state IDLE" << std::endl;
}

void UpdatePortfolioSignal(EventQueue &eventQueue, Event *event, Strategy *strategy, PortfolioHandler &portfolio)
{
    std::cout << "updating porfolio with new signal\n";
    // This will always be a signal event
    SignalEvent* signalEvent = dynamic_cast<SignalEvent*>(event);
    if (signalEvent) {
        portfolio.SignalUpdate(eventQueue, signalEvent);
    } else {
        assert(false && "should only be signal events here");
    }
}

void SendOrderToBroker(EventQueue &eventQueue, Event* event, Strategy *strategy, PortfolioHandler &portfolio)
{

}

void UpdatePortfolioFill(EventQueue &eventQueue, Event *event, Strategy *strategy, PortfolioHandler &portfolio)
{
    std::cout << "updating porfolio with new fill\n";
    // This will always be a fill event
    FillEvent* fillEvent = dynamic_cast<FillEvent*>(event);
    if (fillEvent) {
        portfolio.FillUpdate(eventQueue, fillEvent);
    } else {
        assert(false && "should only be signal events here");
    }
;
}
