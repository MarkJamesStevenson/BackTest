#include <gtest/gtest.h>
#include "../BackTester/orderevent.h"
#include "../BackTester/event.h"
#include <sstream>
#include "../BackTester/event.h"

TEST (OrderEventTest, Create) {
    OrderEvent orderEvent("BLMB", Event::OrderType::LIM, 10.0, Event::Direction::BUY);
    EXPECT_EQ(orderEvent.GetEventType(), Event::EventType::ORDER_EVENT);
}

TEST (OrderEventTest, OutputStream) {
    OrderEvent ev("BLMB", Event::OrderType::LIM, 10, Event::Direction::BUY);
    std::ostringstream os;
    os << ev;
    EXPECT_EQ(os.str(), "Order: Symbol=BLMB Order type=LIM Quantity=10 Direction=BUY");
}


