#include <gtest/gtest.h>
#include "../BackTester/fillevent.h"
#include "../BackTester/ievent.h"

TEST (FillEvent, Create) {
    FillEvent e("BLMB", "LSE", 10, IEvent::Direction::BUY, 30.4, [] ()
    {
        return 19.0;
    });
    EXPECT_EQ(e.getCommission(), 19.0);
}
