#include "dataprovider.h"
#include "marketevent.h"
#include <cassert>

void DataProvider::UpdateBars()
{
    assert(DataAvailable() && "Should not call without checking it has data");
    emit PublishMarketEvent(MarketEvent(bars.back()));
    bars.pop_back();
}

bool DataProvider::DataAvailable() const
{
    return !bars.empty();
}
