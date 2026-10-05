#include <windows.h>

// Función para obtener los detalles de uso de memoria RAM.
// Devuelve verdadero en caso de éxito, falso en caso de error.
bool get_ram_usage_bytes(unsigned long long* totalPhys, unsigned long long* availPhys, DWORD* memoryLoad) {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if (GlobalMemoryStatusEx(&memInfo)) {
        if (totalPhys) *totalPhys = memInfo.ullTotalPhys;
        if (availPhys) *availPhys = memInfo.ullAvailPhys;
        if (memoryLoad) *memoryLoad = memInfo.dwMemoryLoad;
        return true;
    }
    return false;
}
