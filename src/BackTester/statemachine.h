#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <array>
#include "event.h"
#include <iostream>
#include "enums.h"
#include "transition.h"
#include "eventqueue.h"
#include "internalevent.h"

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

    static void MarketEventAction(EventQueue& eventQueue)
    {
        std::cout << "the action when we move from idle to strategy\n\n";
        eventQueue.AddEvent(std::make_unique<InternalEvent>());
    }

    static void InternalEventAction(EventQueue&)
    {
        std::cout << "internal event\n\n";
    }

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


    State currentState = State::IDLE;

    std::array<Transition, 6> stateTransitions = {{
        //CURRENT STATE                    EVENT                              NEXT STATE                       ACTION
        { State::IDLE,                  Event::EventType::MARKET_EVENT,    State::STRATEGY_CALCULATION,  &StateMachine::MarketEventAction },
        { State::STRATEGY_CALCULATION,  Event::EventType::SIGNAL_EVENT,    State::PORTFOLIO_CALCULATION, &StateMachine::MarketEventAction },
        { State::STRATEGY_CALCULATION,  Event::EventType::INTERNAL_EVENT,  State::IDLE,                  &StateMachine::InternalEventAction },
        { State::PORTFOLIO_CALCULATION, Event::EventType::ORDER_EVENT,     State::STRATEGY_CALCULATION,  &StateMachine::MarketEventAction },
        { State::ORDER_ENTRY,           Event::EventType::FILL_EVENT,      State::PORTFOLIO_CALCULATION, &StateMachine::MarketEventAction },
        { State::PORTFOLIO_CALCULATION, Event::EventType::INTERNAL_EVENT,  State::IDLE,                  &StateMachine::MarketEventAction }
    }};
};

#endif // STATEMACHINE_H
