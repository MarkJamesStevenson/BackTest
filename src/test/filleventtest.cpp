#include <gtest/gtest.h>
#include "fillevent.h"
#include "event.h"

TEST (FillEvent, Create) {
    FillEvent fill("BLMB", "LSE", 10, FillEvent::Direction::BUY, 30.4, 19.0);
    EXPECT_EQ(fill.GetEventType(), Event::EventType::FILL_EVENT);
    EXPECT_EQ(fill.GetCommission(), 19.0);
}
