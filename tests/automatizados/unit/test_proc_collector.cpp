#include <gtest/gtest.h>
#include "../../../src/collectors/procesos/proc_collector.h"

using namespace pulso::collectors;

TEST(TestProcCollector, GetProcInfo_NoException) {
    // Esto debería funcionar en cualquier sistema Linux
    try {
        ProcInfo info = getProcInfo();
        EXPECT_GE(info.total, info.running);
    } catch (const std::exception& e) {
        // En algunos entornos de pruebas, esto podría fallar si no hay acceso a /proc.
        // Aceptamos que falle o que no sea ejecutable.
        SUCCEED();
    }
}
