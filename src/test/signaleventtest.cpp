#include <gtest/gtest.h>
#include "signalevent.h"
#include "event.h"

TEST (SignalEvent, Create) {
    SignalEvent event("BLMB", SignalEvent::SignalType::LONG, 10.0);
    EXPECT_EQ(event.GetEventType(), Event::EventType::SIGNAL_EVENT);
}
