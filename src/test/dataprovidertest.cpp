#include "../BackTester/dataprovider.h"
#include "../BackTester/eventqueue.h"
#include "gtest/gtest.h"

TEST (DataProvider, UpdateBarsWithEmptyEventQueue) {
    EventQueue eventQueue;
    DataProvider dataProvider;
    EXPECT_DEATH(dataProvider.UpdateBars(), "Should not call without checking it has data");
}

TEST (DataProvider, UpdateBars) {
    EventQueue eventQueue;
    DataProvider dataProvider;
    EXPECT_DEATH(dataProvider.UpdateBars(), "Should not call without checking it has data");
}
