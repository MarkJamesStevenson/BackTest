#include <gtest/gtest.h>
#include "../BackTester/returntoidleevent.h"
#include "../BackTester/event.h"

TEST (ReturnToIdleEvent, Create) {
    ReturnToIdleEvent ev;
    EXPECT_EQ(ev.GetEventType(), Event::EventType::RETURN_TO_IDLE);
}
