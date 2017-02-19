#include "statemachine.h"
#include <algorithm>
#include <iostream>

void StateMachine::DoTransition(EventQueue &eventQueue, Event::EventType event)
{
    auto it = std::find_if(std::begin(stateTransitions), std::end(stateTransitions), [this, event] (const auto& transition) {
        return transition.currentState == currentState &&
               transition.event == event;
    });
    if (it != std::end(stateTransitions)) {
        it->actionFunction(eventQueue);
        currentState = it->nextState;
    } else {
        std::cout << "could not complete transition, remaining in current state" << std::endl;
    }
}
