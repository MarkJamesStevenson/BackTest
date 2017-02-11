#ifndef IEVENT_H
#define IEVENT_H

class IEvent
{
public:
    IEvent() = default;

    virtual ~IEvent() = default;

    enum class Event_Type
    {
        MARKET_EVENT,
        SIGNAL_EVENT,
        ORDER_EVENT,
        FILL_EVENT
    };

    virtual Event_Type GetEventType() const = 0;
};

#endif // IEVENT_H
