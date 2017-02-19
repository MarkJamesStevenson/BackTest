#ifndef RETURNTOIDLEEVENT_H
#define RETURNTOIDLEEVENT_H

#include "event.h"

class ReturnToIdleEvent : public Event
{
public:
    ReturnToIdleEvent() : Event(Event::EventType::RETURN_TO_IDLE) {}
};

#endif // RETURNTOIDLEEVENT_H
