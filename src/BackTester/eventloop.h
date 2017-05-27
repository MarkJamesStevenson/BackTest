#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <QApplication>
#include "marketevent.h"
#include <QTimer>
#include <QObject>
#include <memory>

class Broker;
class PortfolioHandler;
class DataProvider;
class Strategy;
class QMainWindow;
class QString;

class EventLoop : public QObject
{
    Q_OBJECT
public:
    EventLoop();

signals:
    void EventLoopCompleted() const;
    void ErrorMessage(const QString& error);

public slots:
    void Run(QObject *ui);

private slots:
    void UpdateBars() const;
private:
    void AssignListeners(Broker *broker, PortfolioHandler *portfolio, DataProvider *dataProvider, Strategy *strategy, QObject *ui) const;

    QTimer* updateBarsTimer;
    std::shared_ptr<DataProvider> dataProvider = nullptr;
    std::shared_ptr<Broker> broker = nullptr;
    std::shared_ptr<PortfolioHandler> portfolio = nullptr;
    std::unique_ptr<Strategy> strategy = nullptr;
};

#endif // EVENTLOOP_H
