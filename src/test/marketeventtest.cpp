#include <gtest/gtest.h>
#include "../BackTester/marketevent.h"
#include "../BackTester/ohlcdatapoint.h"

TEST (MarketEvent, Create) {
    OHLCDataPoint data("date",10, 5, 15, 20, 50, 10);
    MarketEvent mktEvent(data);
}
