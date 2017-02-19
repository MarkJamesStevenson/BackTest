#ifndef INTERNALEVENT_H
#define INTERNALEVENT_H

#include "event.h"

class InternalEvent : public Event
{
public:
    InternalEvent() : Event(Event::EventType::INTERNAL_EVENT) {}
};

#endif // INTERNALEVENT_H
