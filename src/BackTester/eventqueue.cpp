#include "eventqueue.h"

void EventQueue::AddEvent(std::unique_ptr<IEvent> event)
{
    queue.push(std::move(event));
}

std::unique_ptr<IEvent> EventQueue::GetNextEvent()
{
    std::unique_ptr<IEvent> event = std::move(queue.front());
    queue.pop();
    return event;
}

bool EventQueue::IsEmpty() const
{
    return queue.empty();
}
