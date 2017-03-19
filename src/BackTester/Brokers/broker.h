#ifndef BROKER_H
#define BROKER_H

class EventQueue;
class OrderEvent;

class Broker
{
public:
    Broker() = default;

    virtual ~Broker() = default;

    virtual void ExecuteOrder(const OrderEvent& event) = 0;
};

#endif // BROKER_H
