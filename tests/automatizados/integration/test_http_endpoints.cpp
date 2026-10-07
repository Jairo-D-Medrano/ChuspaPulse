#include <gtest/gtest.h>
#include <httplib.h>
#include <nlohmann/json.hpp>

// Helper para validar JSON
void VerifyEndpoint(const std::string& path, const std::string& expected_structure_field = "") {
    httplib::Client cli("localhost", 8080);
    auto res = cli.Get(path.c_str());

    ASSERT_TRUE(res != nullptr) << "No hubo respuesta del servidor en: " << path;
    EXPECT_EQ(res->status, 200) << "Error en el endpoint: " << path << ". Código: " << res->status;
    
    if (res->status == 200) {
        try {
            nlohmann::json j = nlohmann::json::parse(res->body);
            if (!expected_structure_field.empty()) {
                EXPECT_TRUE(j.contains(expected_structure_field)) << "JSON en " << path << " no contiene campo: " << expected_structure_field;
            }
        } catch (const nlohmann::json::parse_error& e) {
            FAIL() << "Error al parsear JSON en " << path << ": " << e.what();
        }
    }
}

TEST(HttpIntegrationTest, HealthEndpoint) {
    VerifyEndpoint("/health", "status");
}

TEST(HttpIntegrationTest, MetricsEndpoint) {
    VerifyEndpoint("/metrics"); // Asumiendo que devuelve JSON
}

TEST(HttpIntegrationTest, MetricsHistoryEndpoint) {
    VerifyEndpoint("/metrics/history");
}

TEST(HttpIntegrationTest, ConfigEndpoint) {
    VerifyEndpoint("/config", "http_port");
}

TEST(HttpIntegrationTest, AlertsEndpoint) {
    VerifyEndpoint("/alerts");
}

TEST(HttpIntegrationTest, VersionEndpoint) {
    VerifyEndpoint("/version", "version");
}

TEST(HttpIntegrationTest, MetricsPrometheusEndpoint) {
    // Prometheus suele devolver texto plano, no JSON. Ajustar validación.
    httplib::Client cli("localhost", 8080);
    auto res = cli.Get("/metrics/prometheus");
    ASSERT_TRUE(res != nullptr);
    EXPECT_EQ(res->status, 200);
}
