#include "dataprovider.h"
#include "eventqueue.h"
#include "marketevent.h"
#include <cassert>

void DataProvider::UpdateBars(EventQueue& eventQueue)
{
    assert(DataAvailable() && "Should not call without checking it has data");
    eventQueue.AddEvent(std::make_unique<MarketEvent>(bars.back()));
    bars.pop_back();
}

bool DataProvider::DataAvailable() const
{
    return !bars.empty();
}
