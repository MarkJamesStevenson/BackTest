#ifndef PORTFOLIOHANDLER_H
#define PORTFOLIOHANDLER_H

class SignalEvent;
class MarketEvent;
class FillEvent;
class EventQueue;

class PortfolioHandler
{
public:
    // Set up the portfolio with an initial capital and the volume of shares to
    // buy on each transaction
    PortfolioHandler(double initialCapital = 1000, int volumePerTransaction = 10) :
        capital(initialCapital),
        volumePerTransaction(volumePerTransaction),
        volumeInvested(0)
    {}

    void SignalUpdate(EventQueue& eventQueue, SignalEvent *signalEvent);

    void FillUpdate(EventQueue &eventQueue, FillEvent* fillEvent);

    // Every heartbeat we need to update the current price of our holdings
    void MarketUpdate(MarketEvent* marketEvent);

private:
    double capital;
    int volumePerTransaction;
    int volumeInvested;
};

#endif // PORTFOLIOHANDLER_H
