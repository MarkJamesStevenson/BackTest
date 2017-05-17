#ifndef STRATEGY_H
#define STRATEGY_H

#include <QApplication>
#include <memory>

class MarketEvent;
class SignalEvent;
class PortfolioHandler;

class Strategy : public QObject
{
    Q_OBJECT
public:   
    Strategy(const std::shared_ptr<PortfolioHandler>& portfolio) : portfolio(portfolio)
    {}

    virtual ~Strategy() = default;

public slots:
    virtual void ProcessMarketEvent(const MarketEvent& marketEvent) = 0;

protected:
    std::shared_ptr<PortfolioHandler> portfolio;
};

#endif // STRATEGY_H
