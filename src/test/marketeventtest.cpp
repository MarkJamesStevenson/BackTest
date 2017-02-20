#include <gtest/gtest.h>
#include "../BackTester/marketevent.h"
#include "../BackTester/ohlcdatapoint.h"
#include <sstream>
#include "../BackTester/event.h"

TEST (MarketEvent, Create) {
    OHLCDataPoint data("date",10, 5, 15, 20, 50, 10);
    MarketEvent mktEvent(data);
    EXPECT_EQ(mktEvent.GetEventType(), Event::EventType::MARKET_EVENT);
}

TEST (MarketEvent, OutputEvent) {
    OHLCDataPoint data("date",10, 5, 15, 20, 50, 10);
    MarketEvent mktEvent(data);
    std::ostringstream stream;
    stream << mktEvent;
    std::string expected("Market data received:\n Date: date Open: 10 High: 5 Low: 15 Close: 20 Volume: 50 Adjusted Close 10");
    EXPECT_EQ(stream.str(), expected);
}
