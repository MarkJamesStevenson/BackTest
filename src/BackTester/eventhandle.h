#ifndef EVENTHANDLE_H
#define EVENTHANDLE_H

#include <memory>
#include "ievent.h"

class EventHandle
{
public:
    EventHandle(IEvent::Event_Type eventType);

    IEvent::Event_Type GetEventType() const;

    EventHandle(EventHandle&& rhs);
    EventHandle& operator=(EventHandle&& rhs);

    EventHandle(const EventHandle&) = delete;
    EventHandle& operator=(const EventHandle&) = delete;

private:
    std::unique_ptr<IEvent> event = nullptr;
};

#endif // EVENTHANDLE_H
