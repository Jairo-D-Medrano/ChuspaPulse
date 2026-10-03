#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include "../../../src/collectors/bateria/bateria_collector.hpp"

namespace fs = std::filesystem;
using namespace pulso::collectors::bateria;

class TestBateriaCollector : public ::testing::Test {
protected:
    void SetUp() override {
        test_dir = fs::temp_directory_path() / "test_bat_dir";
        fs::create_directory(test_dir);
    }

    void TearDown() override {
        fs::remove_all(test_dir);
    }

    fs::path test_dir;
};

TEST_F(TestBateriaCollector, GetBateriaInfo_Exitoso) {
    // Crear archivos de prueba
    std::ofstream capacity_file(test_dir / "capacity");
    capacity_file << "80";
    capacity_file.close();

    std::ofstream status_file(test_dir / "status");
    status_file << "Discharging";
    status_file.close();

    BateriaInfo info = getBateriaInfo(test_dir.string());

    EXPECT_TRUE(info.disponible);
    EXPECT_EQ(info.porcentaje, 80);
    EXPECT_EQ(info.estado, "Discharging");
}

TEST_F(TestBateriaCollector, GetBateriaInfo_NoDisponible) {
    // Directorio vacío, no debería lanzar excepción y debe marcar no disponible
    BateriaInfo info = getBateriaInfo(test_dir.string());

    EXPECT_FALSE(info.disponible);
}

TEST(TestCollectorBateria, NombreEsCorrecto) {
    CollectorBateria collector;
    EXPECT_EQ(collector.nombre(), "bateria");
}
