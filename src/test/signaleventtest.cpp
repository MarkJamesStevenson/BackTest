#include <gtest/gtest.h>
#include "../BackTester/signalevent.h"

TEST (SignalEvent, Create) {
    SignalEvent event("BLMB", SignalEvent::SignalType::LONG);
    EXPECT_EQ(event.GetEventType(), SignalEvent::Event_Type::SIGNAL_EVENT);
}
