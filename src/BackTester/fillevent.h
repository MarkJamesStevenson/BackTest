#ifndef FILLEVENT_H
#define FILLEVENT_H

#include "ievent.h"

class FillEvent : public IEvent
{
public:
    FillEvent() : IEvent(Event_Type::FILL_EVENT) {}
};

#endif // FILLEVENT_H
