#include <gtest/gtest.h>
#include "../../../src/collectors/temperatura/temp_collector.h"

using namespace collectors;

TEST(TestTempCollector, GetTempInfo_Basico) {
    // Esto dependerá de si el sistema tiene el archivo, pero el código
    // de producción garantiza que no lanza excepción.
    TempInfo info = getTempInfo();
    
    // Si no hay acceso al archivo, debe retornar disponible=false.
    // Si hay acceso, el valor de temperatura debe ser >= 0.
    if (info.disponible) {
        EXPECT_GE(info.cpu_celsius, 0.0f);
    } else {
        EXPECT_EQ(info.cpu_celsius, 0.0f);
    }
}
