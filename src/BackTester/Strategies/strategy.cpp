#include "strategy.h"
#include <QObject>
#include "dataprovider.h"

Strategy::Strategy(DataProvider* dataProvider)
{
    QObject::connect(dataProvider, SIGNAL(BarsUpdate(const MarketEvent&)),
                     this, SLOT(ProcessMarketEvent(const MarketEvent&)));
}
