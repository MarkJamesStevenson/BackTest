#include "strategy.h"
#include <QObject>
#include "dataprovider.h"
#include "portfoliohandler.h"

Strategy::Strategy(DataProvider* dataProvider, PortfolioHandler *portfolio) :
    portfolio(portfolio)
{
    QObject::connect(dataProvider, SIGNAL(PublishMarketEvent(const MarketEvent&)),
                     this, SLOT(ProcessMarketEvent(const MarketEvent&)));
}
