#include "main.h"
#include "mailbox.h"
#include "cmsis_os.h"

static osMutexId Mailbox_Mutex;
static osSemaphoreId DataAvailable_Sem;
static osSemaphoreId BufferEmpty_Sem;

BaseType_t Mailbox_Init(Mailbox_t* handle) {
	BaseType_t retVal = pdTRUE;

    // 1. Inicialización del Mutex (para exclusión mutua)
     Mailbox_Mutex = osMutexNew(NULL);

    // 2. Inicialización del Semáforo de Disponibilidad de Datos (Estado inicial: 0)
     DataAvailable_Sem = osSemaphoreNew(1, 0, NULL); 
    
    // 3. Inicialización del Semáforo de Buffer Vacío (Estado inicial: 1)
     BufferEmpty_Sem = osSemaphoreNew(1, 1, NULL); 
    
    // 4. Comprobación y retorno
    if ( Mailbox_Mutex == NULL || 
         DataAvailable_Sem == NULL || 
         BufferEmpty_Sem == NULL)  {
        // ("ERROR: Fallo al crear un recurso del Mailbox.\n");
        retVal = pdFALSE;
    }

    handle->data = 0;
    return retVal;
}

BaseType_t Mailbox_Post(Mailbox_t *handle, int new_data)
{
    if (handle == NULL)
    	return pdFALSE; // Validación básica

    // 1. Espera a que el Buffer esté vacío (liberado por el receptor)
    osSemaphoreAcquire( BufferEmpty_Sem, osWaitForever);

    // 2. Adquiere Mutex (Exclusión Mutua)
    osMutexAcquire( Mailbox_Mutex, osWaitForever);

    // 3. Escribe el dato
    handle->data = new_data;

    // 4. Libera Mutex
    osMutexRelease( Mailbox_Mutex);

    // 5. Señala que hay un Dato Disponible (despierta al receptor)
    osSemaphoreRelease( DataAvailable_Sem);

    return pdTRUE;
}

int Mailbox_Pend(Mailbox_t *mailbox_handle)
{
    if (handle == NULL) 
        return -1; // Validación básica

    int read_temp;

    // 1. Espera a que haya un Dato Disponible (señalado por el remitente)
    osSemaphoreAcquire( DataAvailable_Sem, osWaitForever);

    // 2. Adquiere Mutex (Exclusión Mutua)
    osMutexAcquire( Mailbox_Mutex, osWaitForever);

    // 3. Lee el dato
    read_temp = handle->data;

    // 4. Libera Mutex
    osMutexRelease( Mailbox_Mutex);

    // 5. Señala que el Buffer está Vacío (despierta al remitente)
    osSemaphoreRelease( BufferEmpty_Sem);

    return read_temp;
}
