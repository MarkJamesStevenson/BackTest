#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <QApplication>

class Broker;
class PortfolioHandler;
class DataProvider;
class Strategy;
class QMainWindow;

class EventLoop : public QObject
{
    Q_OBJECT
public:
    EventLoop() = default;

    void Run(QMainWindow* ui) const;

private:
    void AssignListeners(QMainWindow *ui, Broker *broker, PortfolioHandler *portfolio, DataProvider *dataProvider, Strategy *strategy) const;
};

#endif // EVENTLOOP_H
