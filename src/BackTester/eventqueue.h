#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <queue>
#include <memory>
#include "event.h"

class EventQueue
{
public:
    EventQueue() = default;

    void AddEvent(std::unique_ptr<Event> event);

    std::unique_ptr<Event> GetNextEvent();

    bool IsEmpty() const;

private:
    std::queue<std::unique_ptr<Event>> queue;
};

#endif // EVENTQUEUE_H
