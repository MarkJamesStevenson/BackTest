#ifndef BROKER_H
#define BROKER_H

#include <QApplication>

class OrderEvent;
class FillEvent;

class Broker : public QObject
{
    Q_OBJECT
public:
    Broker() = default;

    virtual ~Broker() = default;

    template<typename T>
    void AssignFillEventListener(T* listener)
    {
        QObject::connect(this, SIGNAL(PublishFillEvent(const FillEvent&)),
                         listener, SLOT(ProcessFillEvent(const FillEvent&)));
    }

    virtual void ProcessOrderEvent(const OrderEvent& orderEvent) = 0;

signals:
    void PublishFillEvent(const FillEvent&);
};

#endif // BROKER_H
