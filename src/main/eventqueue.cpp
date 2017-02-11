#include "eventqueue.h"

void EventQueue::AddEventToQueue(std::unique_ptr<IEvent> event)
{
    queue.push(event);
}

std::unique_ptr<IEvent> EventQueue::GetNextEvent()
{
    std::unique_ptr<IEvent> event = std::move(queue.front());
    queue.pop();
    return event;
}
