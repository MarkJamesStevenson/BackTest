#include "eventloop.h"
#include "dataprovider.h"
#include "broker.h"
#include "portfoliohandler.h"
#include "strategy.h"
#include "buyandholdstrategy.h"
#include "interactivebrokers.h"
#include "dataproviderfactory.h"
#include <string>

EventLoop::EventLoop() :
    updateBarsTimer(new QTimer(this))
{
    updateBarsTimer->setSingleShot(false);
    connect(updateBarsTimer, SIGNAL(timeout()), this, SLOT(UpdateBars()));
}

void EventLoop::Run(QObject* ui)
{
    try {
        DataProviderFactory dataProviderFactory;
        dataProvider = dataProviderFactory.CreateDataProvider(DataSource::YAHOOCSVFILEDATAPROVIDER, "MSFT.csv");
    } catch (const std::exception& e) {
        QString error("Unable to continue as could not create data provider. \n" + QString(e.what()));
        emit ErrorMessage(error);
        return;
    }
    broker = std::make_shared<InteractiveBrokers>();
    portfolio = std::make_shared<PortfolioHandler>(broker);
    strategy = std::make_unique<BuyAndHoldStrategy>(portfolio);
    AssignListeners(broker.get(), portfolio.get(), dataProvider.get(), strategy.get(), ui);
    updateBarsTimer->start(1);
}

void EventLoop::UpdateBars() const
{
    if (dataProvider->DataAvailable())
    {
        dataProvider->UpdateBars();
    }
    else
    {
        updateBarsTimer->stop();
        emit EventLoopCompleted();
    }
}

void EventLoop::AssignListeners(Broker* broker, PortfolioHandler* portfolio, DataProvider* dataProvider, Strategy* strategy, QObject* ui) const
{
    dataProvider->AssignMarketEventListener(ui);
    dataProvider->AssignMarketEventListener(portfolio);
    dataProvider->AssignMarketEventListener(strategy);
    broker->AssignFillEventListener(portfolio);
}

