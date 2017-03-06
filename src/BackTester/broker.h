#ifndef BROKER_H
#define BROKER_H

class EventQueue;
class OrderEvent;

class Broker
{
public:
    Broker() = default;

    virtual ~Broker() = default;

    // This should always add a fill event to the eventqueue
    virtual void ExecuteOrder(EventQueue& eventQueue, OrderEvent* event) = 0;
};

#endif // BROKER_H
