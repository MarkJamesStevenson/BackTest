#ifndef PORTFOLIOHANDLER_H
#define PORTFOLIOHANDLER_H

#include <QApplication>
#include <memory>
#include "broker.h"

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
    PortfolioHandler(const std::shared_ptr<Broker> broker,
                     double initialCapital = 1000000,
                     int volumePerTransaction = 10) :
        broker(broker),
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

    void BuyOrderRequest(const SignalEvent& signalEvent);
    void SellOrderRequest(const SignalEvent& signalEvent);
    void ExitOrderRequest(const SignalEvent& signalEvent);

public slots:
    // Every heartbeat we need to update the current price of our holdings
    void ProcessMarketEvent(const MarketEvent& marketEvent);
    // Receive updates from the broker if we get any fills
    void ProcessFillEvent(const FillEvent& fillEvent);

private:
    std::shared_ptr<Broker> broker;
    double capital;
    int volumePerTransaction;
    int volumeInvested;
    double capitalInvested;
};

#endif // PORTFOLIOHANDLER_H
