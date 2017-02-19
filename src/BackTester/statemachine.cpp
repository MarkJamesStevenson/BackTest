#include "statemachine.h"
#include <algorithm>
#include <iostream>
#include "returntoidleevent.h"

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
        std::cerr << "could not complete transition, remaining in current state" << std::endl;
    }
}

void MarketEventAction(EventQueue &eventQueue)
{
    std::cout << "the action when we move from idle to strategy\n\n";
    eventQueue.AddEvent(std::make_unique<ReturnToIdleEvent>());
}

void InternalEventAction(EventQueue &)
{
    std::cout << "internal event\n\n";
}
