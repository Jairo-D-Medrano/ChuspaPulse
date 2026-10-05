#include <windows.h>

// Función para obtener el estado de la batería usando GetSystemPowerStatus
void get_battery_status() {
    SYSTEM_POWER_STATUS status;
    
    // Obtener el estado del sistema de alimentación
    if (GetSystemPowerStatus(&status)) {
        // Aquí se procesarían los datos de status
        // status.BatteryLifePercent contiene el porcentaje
        // status.ACLineStatus indica si está conectado a la red eléctrica
    }
}
