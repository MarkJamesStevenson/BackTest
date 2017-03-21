#ifndef BROKER_H
#define BROKER_H

#include <QObject>

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

signals:
    void PublishFillEvent(const FillEvent&);

public slots:
    virtual void ProcessOrderEvent(const OrderEvent& signalEvent) = 0;
};

#endif // BROKER_H
