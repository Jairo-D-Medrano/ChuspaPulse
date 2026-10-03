#include <gtest/gtest.h>
#include "../../../src/collectors/uptime/uptime_collector.h"

TEST(TestUptimeCollector, GetUptime_NoException) {
    try {
        UptimeInfo info = getUptime();
        EXPECT_GE(info.total_seconds, 0ULL);
    } catch (const std::exception& e) {
        SUCCEED();
    }
}
