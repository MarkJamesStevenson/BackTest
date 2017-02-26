#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <array>
#include "event.h"
#include "eventqueue.h"
#include <functional>
#include "strategy.h"
#include "portfoliohandler.h"

class StateMachine
{
public:

    StateMachine() = default;

    enum class State {
        IDLE,
        STRATEGY_CALCULATION,
        PORTFOLIO_CALCULATION,
        ORDER_ENTRY,
    };

    StateMachine(const StateMachine&) = delete;
    StateMachine& operator=(const StateMachine&) = delete;

    void DoTransition(EventQueue& eventQueue, Event* event, Strategy *strategy, PortfolioHandler& portfolio);

    State GetCurrentState() const { return currentState; }

private:
    struct Transition
    {
        Transition(State currentState, Event::EventType event, State nextState, std::function<void(EventQueue&, Event*, Strategy*, PortfolioHandler&)> actionFunction) :
            currentState(currentState), event(event), nextState(nextState), actionFunction(actionFunction)
        {}

        State currentState;
        Event::EventType event;
        State nextState;
        std::function<void(EventQueue&, Event*, Strategy*, PortfolioHandler&)> actionFunction;
    };

    // We always start at the idle state
    State currentState = State::IDLE;

    static const std::array<Transition, 6> stateTransitions;
};

void UpdateStrategyBars(EventQueue& eventQueue, Event* event, Strategy* strategy, PortfolioHandler& portfolio);
void ReturnToIdleState(EventQueue& eventQueue, Event *event, Strategy* strategy, PortfolioHandler& portfolio);
void UpdatePortfolioSignal(EventQueue& eventQueue, Event* event, Strategy* strategy, PortfolioHandler& portfolio);
void SendOrderToBroker(EventQueue& eventQueue, Event *event, Strategy* strategy, PortfolioHandler& portfolio);
void UpdatePortfolioFill(EventQueue& eventQueue, Event* event, Strategy* strategy, PortfolioHandler& portfolio);

#endif // STATEMACHINE_H
