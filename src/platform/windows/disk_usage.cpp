#include <windows.h>

// Función para obtener el espacio total y libre en disco en bytes para una ruta de unidad específica.
// Devuelve verdadero en caso de éxito, falso en caso de error.
bool get_disk_usage_bytes(const char* rootPath, unsigned long long* totalBytes, unsigned long long* freeBytes) {
    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;

    if (GetDiskFreeSpaceExA(rootPath, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
        if (totalBytes) *totalBytes = totalNumberOfBytes.QuadPart;
        if (freeBytes) *freeBytes = freeBytesAvailable.QuadPart;
        return true;
    }
    return false;
}
