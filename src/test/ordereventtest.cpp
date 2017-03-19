#include <gtest/gtest.h>
#include "orderevent.h"
#include "event.h"
#include <sstream>
#include "event.h"

TEST (OrderEventTest, Create) {
    OrderEvent orderEvent("BLMB", Event::OrderType::LIM, 10, 19.0, Event::Direction::BUY);
    EXPECT_EQ(orderEvent.GetEventType(), Event::EventType::ORDER_EVENT);
}

TEST (OrderEventTest, OutputStream) {
    OrderEvent ev("BLMB", Event::OrderType::LIM, 10, 19.0, Event::Direction::BUY);
    std::ostringstream os;
    os << ev;
    EXPECT_EQ(os.str(), "Order: Symbol=BLMB Order type=LIM Volume=10 Direction=BUY");
}


