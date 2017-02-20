#include <gtest/gtest.h>
#include "../BackTester/signalevent.h"
#include "../BackTester/event.h"

TEST (SignalEvent, Create) {
    SignalEvent event("BLMB", SignalEvent::SignalType::LONG);
    EXPECT_EQ(event.GetEventType(), Event::EventType::SIGNAL_EVENT);
}
