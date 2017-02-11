#ifndef IEVENT_H
#define IEVENT_H

class IEvent
{
public:

    enum class Event_Type
    {
        MARKET_EVENT,
        SIGNAL_EVENT,
        ORDER_EVENT,
        FILL_EVENT
    };

    IEvent(Event_Type e) : event(e) {}

    virtual ~IEvent() = default;

    Event_Type GetEventType() const
    {
        return event;
    }

protected:
    Event_Type event;
};

#endif // IEVENT_H
