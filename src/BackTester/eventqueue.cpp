#include "eventqueue.h"
#include <cassert>

void EventQueue::AddEvent(std::unique_ptr<Event> event)
{
    queue.push(std::move(event));
}

std::unique_ptr<Event> EventQueue::GetNextEvent()
{
    assert(!IsEmpty() && "Should not call with empty queue");
    auto event = std::move(queue.front());
    queue.pop();
    return event;
}

bool EventQueue::IsEmpty() const
{
    return queue.empty();
}
