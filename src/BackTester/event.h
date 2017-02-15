#ifndef EVENT_H
#define EVENT_H

class Event
{
public:

    Event() = default;

    virtual ~Event() = default;

    virtual void DoAction() = 0;

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
};

#endif // EVENT_H
