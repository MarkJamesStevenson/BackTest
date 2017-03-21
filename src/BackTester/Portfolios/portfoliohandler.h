#ifndef PORTFOLIOHANDLER_H
#define PORTFOLIOHANDLER_H

#include <QObject.h>

class SignalEvent;
class MarketEvent;
class FillEvent;
class DataProvider;
class OrderEvent;

class PortfolioHandler : public QObject
{
    Q_OBJECT
public:
    // Set up the portfolio with an initial capital and the volume of shares to
    // buy on each transaction, the initial capital is in GBX
    PortfolioHandler::PortfolioHandler(double initialCapital = 1000000, int volumePerTransaction = 10) :
        capital(initialCapital),
        volumePerTransaction(volumePerTransaction),
        volumeInvested(0),
        capitalInvested(0.0)
    {}

    void FillUpdate(const FillEvent& fillEvent);

    template<typename T>
    void AssignOrderEventListener(T* listener)
    {
        QObject::connect(this, SIGNAL(PublishOrderEvent(const OrderEvent&)),
                         listener, SLOT(ProcessOrderEvent(const OrderEvent&)));
    }

signals:
    void PublishOrderEvent(const OrderEvent&);

    // Every heartbeat we need to update the current price of our holdings
public slots:
    void ProcessMarketEvent(const MarketEvent& marketEvent);
    void ProcessBuySignalEvent(const SignalEvent& signalEvent);
    void ProcessSellSignalEvent(const SignalEvent& signalEvent);
    void ProcessExitSignalEvent(const SignalEvent& signalEvent);

private:
    double capital;
    int volumePerTransaction;
    int volumeInvested;
    double capitalInvested;
};

#endif // PORTFOLIOHANDLER_H
