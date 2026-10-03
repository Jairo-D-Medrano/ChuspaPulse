#include <gtest/gtest.h>
#include "../../../src/collectors/network/net_usage.h"

TEST(TestNetUsage, GetNetUsage_NoException) {
    // getNetUsage no debería lanzar excepciones
    NetInfo info = getNetUsage();
    SUCCEED();
}
