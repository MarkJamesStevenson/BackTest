#ifndef STRATEGY_H
#define STRATEGY_H

#include <QObject>
class DataProvider;
class MarketEvent;
class SignalEvent;
class PortfolioHandler;

class Strategy : public QObject
{
    Q_OBJECT
public:   
    Strategy() = default;

    virtual ~Strategy() = default;

    template<typename T>
    void AssignSignalEventListener(T* listener)
    {
        QObject::connect(this, SIGNAL(PublishBuySignalEvent(const SignalEvent&)),
                         listener, SLOT(ProcessBuySignalEvent(const SignalEvent&)));
        QObject::connect(this, SIGNAL(PublishSellSignalEvent(const SignalEvent&)),
                         listener, SLOT(ProcessSellSignalEvent(const SignalEvent&)));
        QObject::connect(this, SIGNAL(PublishExitSignalEvent(const SignalEvent&)),
                         listener, SLOT(ProcessExitSignalEvent(const SignalEvent&)));
    }

signals:
    void PublishBuySignalEvent(const SignalEvent&);
    void PublishSellSignalEvent(const SignalEvent&);
    void PublishExitSignalEvent(const SignalEvent&);

public slots:
    virtual void ProcessMarketEvent(const MarketEvent& marketEvent) = 0;

protected:
    PortfolioHandler* portfolio;
};

#endif // STRATEGY_H
