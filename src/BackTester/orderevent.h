#ifndef ORDEREVENT_H
#define ORDEREVENT_H

#include "ievent.h"

class OrderEvent : public IEvent
{
public:
    OrderEvent() : IEvent(Event_Type::ORDER_EVENT) {}
};

#endif // ORDEREVENT_H
