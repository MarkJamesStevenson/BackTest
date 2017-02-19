#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
    enum class EventType;

    Event(EventType event) : event(event) {}

    virtual ~Event() = default;

    EventType GetEventType () { return event; }

    enum class EventType {
        MARKET_EVENT,
        SIGNAL_EVENT,
        ORDER_EVENT,
        FILL_EVENT,
        INTERNAL_EVENT
    };

    enum class Direction {
        BUY,
        SELL
    };

    enum class OrderType {
        MKT, //Market order
        LIM  //Limit order
    };

    enum class SignalType {
        LONG,
        SHORT
    };

private:
    EventType event;
};

#endif // EVENT_H
