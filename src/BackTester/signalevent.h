#ifndef SIGNALEVENT_H
#define SIGNALEVENT_H

#include "ievent.h"

class SignalEvent : public IEvent
{
public:
    SignalEvent() : IEvent(Event_Type::SIGNAL_EVENT) {}
};

#endif // SIGNALEVENT_H
