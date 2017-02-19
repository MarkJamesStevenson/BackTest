#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <array>
#include "event.h"
#include "eventqueue.h"
#include <functional>

void MarketEventAction(EventQueue& eventQueue);
void InternalEventAction(EventQueue&);

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

    void DoTransition(EventQueue& eventQueue, Event::EventType event);

private:
    struct Transition
    {
        Transition(State currentState, Event::EventType event, State nextState, std::function<void(EventQueue&)> actionFunction) :
            currentState(currentState), event(event), nextState(nextState), actionFunction(actionFunction)
        {}

        State currentState;
        Event::EventType event;
        State nextState;
        std::function<void(EventQueue&)> actionFunction;
    };

    // We always start at the idle state
    State currentState = State::IDLE;

    // This array contains all the possible state transitions. The action is a function pointer which implements the
    // functionality for the new state.
    std::array<Transition, 6> stateTransitions = {{
        //CURRENT STATE                 EVENT                              NEXT STATE                    ACTION
        { State::IDLE,                  Event::EventType::MARKET_EVENT,    State::STRATEGY_CALCULATION,  &MarketEventAction },
        { State::STRATEGY_CALCULATION,  Event::EventType::SIGNAL_EVENT,    State::PORTFOLIO_CALCULATION, &MarketEventAction },
        { State::STRATEGY_CALCULATION,  Event::EventType::RETURN_TO_IDLE,  State::IDLE,                  &MarketEventAction },
        { State::PORTFOLIO_CALCULATION, Event::EventType::ORDER_EVENT,     State::STRATEGY_CALCULATION,  &MarketEventAction },
        { State::ORDER_ENTRY,           Event::EventType::FILL_EVENT,      State::PORTFOLIO_CALCULATION, &MarketEventAction },
        { State::PORTFOLIO_CALCULATION, Event::EventType::RETURN_TO_IDLE,  State::IDLE,                  &MarketEventAction }
    }};
};

#endif // STATEMACHINE_H
