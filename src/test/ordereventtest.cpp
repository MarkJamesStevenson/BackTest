#include <gtest/gtest.h>
#include "../BackTester/orderevent.h"
#include "../BackTester/event.h"
#include <sstream>

TEST (OrderEventTest, OutputStream) {
    OrderEvent ev("BLMB", Event::OrderType::LIM, 10, Event::Direction::BUY);
    std::ostringstream os;
    os << ev;
    EXPECT_EQ(os.str(), "Order: Symbol=BLMB Order type=LIM Quantity=10 Direction=BUY");
}


