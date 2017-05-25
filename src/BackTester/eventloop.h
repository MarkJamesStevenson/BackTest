#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <QApplication>
#include "marketevent.h"

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
    EventLoop() = default;

    //void Run(DataProvider *dataProvider) const;

//signals:
    //void UpdateUIWithMarketEvent(const MarketEvent& marketEvent);

public slots:
    void Run(DataProvider *dataProvider) const;

private:
    void AssignListeners(Broker *broker, PortfolioHandler *portfolio, DataProvider *dataProvider, Strategy *strategy) const;
};

#endif // EVENTLOOP_H
