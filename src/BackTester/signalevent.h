#ifndef SIGNALEVENT_H
#define SIGNALEVENT_H

#include "ievent.h"

class SignalEvent : public IEvent
{
public:
    SignalEvent() = default;

    virtual Event_Type GetEventType() const override
    {
        return event;
    }

private:
    Event_Type event = Event_Type::SIGNAL_EVENT;
};

#endif // SIGNALEVENT_H
