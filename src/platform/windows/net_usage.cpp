#include <windows.h>
#include <winsock2.h>
#include <iphlpapi.h>

#pragma comment(lib, "IPHLPAPI.lib")

// Función para obtener información de red usando GetIfTable2
void get_network_usage() {
    PMIB_IF_TABLE2 pIfTable = NULL;
    
    // Obtener la tabla de interfaces
    if (GetIfTable2(&pIfTable) == NO_ERROR) {
        // Aquí se procesarían los datos de pIfTable->Table[i]
        
        // Liberar la memoria asignada por GetIfTable2
        FreeMibTable(pIfTable);
    }
}
