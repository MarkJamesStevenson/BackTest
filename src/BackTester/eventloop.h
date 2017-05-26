#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <QApplication>
#include "marketevent.h"
#include <QTimer>
#include <QObject>

class Broker;
class PortfolioHandler;
class DataProvider;
class Strategy;
class QMainWindow;

//Q_DECLARE_METATYPE(MarketEvent)

class EventLoop : public QObject
{
    Q_OBJECT
public:
    EventLoop(DataProvider* dataProvider) : dataProvider(dataProvider)
    {
        myTimer = new QTimer(this);
       myTimer->setInterval(1);
       myTimer->setSingleShot(false);
       connect(myTimer, SIGNAL(timeout()), this, SLOT(run2()));
    }

signals:
    void EventLoopCompleted() const;

public slots:
    void Run() const;

private slots:
    void run2() const;
private:
    void AssignListeners(Broker *broker, PortfolioHandler *portfolio, DataProvider *dataProvider, Strategy *strategy) const;

    DataProvider* dataProvider;
    QTimer* myTimer;
};

#endif // EVENTLOOP_H
