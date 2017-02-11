#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <queue>
#include <memory>
#include "eventhandle.h"

class EventQueue
{
public:
    EventQueue() = default;

    void AddEvent(EventHandle&& event);

    EventHandle GetNextEvent();

    bool IsEmpty() const;

private:
    std::queue<EventHandle> queue;
};

#endif // EVENTQUEUE_H
