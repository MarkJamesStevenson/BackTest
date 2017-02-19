#ifndef TRANSITION_H
#define TRANSITION_H

#include "event.h"
#include "enums.h"
#include <functional>
#include "eventqueue.h"

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

#endif // TRANSITION_H
