#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
    enum class EventType;

    Event(EventType event) : event(event) {}

    // Trick to make sure event is an ABC. We still define it in the .cpp file.
    virtual ~Event() = 0;

    EventType GetEventType() const { return event; }

    enum class EventType {
        MARKET_EVENT,
        SIGNAL_EVENT,
        ORDER_EVENT,
        FILL_EVENT,
        RETURN_TO_IDLE
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
        SHORT,
        EXIT
    };

private:
    EventType event;
};

#endif // EVENT_H
