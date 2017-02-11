#ifndef ORDEREVENT_H
#define ORDEREVENT_H

#include "ievent.h"

class OrderEvent : public IEvent
{
public:
    OrderEvent() = default;

    virtual Event_Type GetEventType() const override
    {
        return event;
    }

private:
    Event_Type event = Event_Type::ORDER_EVENT;
};

#endif // ORDEREVENT_H
