#include <gtest/gtest.h>
#include "../BackTester/marketevent.h"

TEST (MarketEvent, Create) {
    MarketEvent mktEvent;
    EXPECT_EQ(mktEvent.GetEventType(), MarketEvent::Event_Type::MARKET_EVENT);
}
