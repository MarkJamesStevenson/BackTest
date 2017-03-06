#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <array>
#include "event.h"
#include <functional>

class PortfolioHandler;
class EventQueue;
class Strategy;
class Broker;

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

    void DoTransition(EventQueue& eventQueue, Event* event, Strategy *strategy, PortfolioHandler& portfolio, Broker* broker);

    State GetCurrentState() const { return currentState; }

private:
    struct Transition
    {
        Transition(State currentState, Event::EventType event, State nextState, std::function<void(EventQueue&, Event*, Strategy*, PortfolioHandler&, Broker*)> actionFunction) :
            currentState(currentState), event(event), nextState(nextState), actionFunction(actionFunction)
        {}

        State currentState;
        Event::EventType event;
        State nextState;
        std::function<void(EventQueue&, Event*, Strategy*, PortfolioHandler&, Broker*)> actionFunction;
    };

    // We always start at the idle state
    State currentState = State::IDLE;

    static const std::array<Transition, 6> stateTransitions;
};

void UpdateStrategyBars(EventQueue& eventQueue, Event* event, Strategy* strategy, PortfolioHandler& portfolio, Broker *broker);
void ReturnToIdleState(EventQueue& eventQueue, Event *event, Strategy* strategy, PortfolioHandler& portfolio, Broker* broker);
void UpdatePortfolioSignal(EventQueue& eventQueue, Event* event, Strategy* strategy, PortfolioHandler& portfolio, Broker *broker);
void SendOrderToBroker(EventQueue& eventQueue, Event *event, Strategy* strategy, PortfolioHandler& portfolio, Broker* broker);
void UpdatePortfolioFill(EventQueue& eventQueue, Event* event, Strategy* strategy, PortfolioHandler& portfolio, Broker* broker);

#endif // STATEMACHINE_H
