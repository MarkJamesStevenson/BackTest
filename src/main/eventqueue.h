#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <queue>
#include <memory>
#include "ievent.h"

class EventQueue
{
public:
    EventQueue() = default;

    void AddEventToQueue(std::unique_ptr<IEvent> event);

    std::unique_ptr<IEvent> GetNextEvent();

private:
    std::queue<std::unique_ptr<IEvent>> queue;
};

#endif // EVENTQUEUE_H
