#include "../BackTester/dataprovider.h"
#include "gtest/gtest.h"

TEST (DataProvider, UpdateBarsWithEmptyEventVector) {
    DataProvider dataProvider;
    EXPECT_DEATH(dataProvider.UpdateBars(), "Should not call without checking it has data");
}
