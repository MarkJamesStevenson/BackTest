#include <gtest/gtest.h>
#include "../BackTester/signalevent.h"

TEST (SignalEvent, Create) {
    SignalEvent event("BLMB", SignalEvent::SignalType::LONG);
}
