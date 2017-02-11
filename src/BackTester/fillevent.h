#ifndef FILLEVENT_H
#define FILLEVENT_H

#include "ievent.h"

class FillEvent : public IEvent
{
public:
    FillEvent() = default;

    virtual Event_Type GetEventType() const override
    {
        return event;
    }

private:
    Event_Type event = Event_Type::FILL_EVENT;
};

#endif // FILLEVENT_H
