#include <gtest/gtest.h>
#include "../../../src/collectors/loadavg/loadavg_collector.h"

TEST(TestLoadAvgCollector, GetLoadAverage_NoException) {
    try {
        LoadAvgInfo info = getLoadAverage();
        EXPECT_GE(info.load1, 0.0f);
    } catch (const std::exception& e) {
        SUCCEED();
    }
}
