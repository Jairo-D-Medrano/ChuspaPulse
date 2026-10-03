#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include "../../../src/collectors/cpu/cpu_usage.hpp"

namespace fs = std::filesystem;

class TestCPUCollector : public ::testing::Test {
protected:
    void SetUp() override {
        test_file = fs::temp_directory_path() / "test_stat";
    }

    void TearDown() override {
        fs::remove(test_file);
    }

    fs::path test_file;
};

TEST_F(TestCPUCollector, LeerEstadisticasCPU_ValoresCorrectos) {
    std::ofstream stat_file(test_file);
    // cpu  user nice system idle iowait irq softirq steal
    stat_file << "cpu  100 20 30 400 5 10 5 0\n";
    stat_file.close();

    ContadoresCPU c = LeerEstadisticasCPU(test_file.string());

    EXPECT_EQ(c.usuario, 100);
    EXPECT_EQ(c.nice, 20);
    EXPECT_EQ(c.sistema, 30);
    EXPECT_EQ(c.ocioso, 400);
    EXPECT_EQ(c.espera_io, 5);
}

TEST_F(TestCPUCollector, CalcularTicks) {
    ContadoresCPU c{100, 20, 30, 400, 5, 10, 5, 0};
    
    EXPECT_EQ(CalcularTicksTotales(c), 100+20+30+400+5+10+5+0);
    EXPECT_EQ(CalcularTicksOciosos(c), 400+5);
}
