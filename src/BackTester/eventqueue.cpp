#include "eventqueue.h"
#include "ievent.h"

void EventQueue::AddEvent(EventHandle&& event)
{
    queue.push(std::move(event));
}

EventHandle EventQueue::GetNextEvent()
{
    EventHandle event = std::move(queue.front());
    queue.pop();
    return event;
}

bool EventQueue::IsEmpty() const
{
    return queue.empty();
}
