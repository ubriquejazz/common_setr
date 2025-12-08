#include "main.h"
#include "mailbox.h"

BaseType_t Mailbox_Init(Mailbox_t* mailbox_handle) {
	BaseType_t retVal = pdTRUE;

    // 1. Inicialización del Mutex (para exclusión mutua)
    mailbox_handle->Mailbox_Mutex = osMutexNew(NULL);

    // 2. Inicialización del Semáforo de Disponibilidad de Datos (Estado inicial: 0)
    mailbox_handle->DataAvailable_Sem = osSemaphoreNew(1, 0, NULL); 
    
    // 3. Inicialización del Semáforo de Buffer Vacío (Estado inicial: 1)
    mailbox_handle->BufferEmpty_Sem = osSemaphoreNew(1, 1, NULL); 
    
    // 4. Comprobación y retorno
    if (mailbox_handle->Mailbox_Mutex == NULL || 
        mailbox_handle->DataAvailable_Sem == NULL || 
        mailbox_handle->BufferEmpty_Sem == NULL) 
    {
        // ("ERROR: Fallo al crear un recurso del Mailbox.\n");
        retVal = pdFALSE;
    }

    mailbox_handle->data = 0;
    return retVal;
}

BaseType_t Mailbox_Post(Mailbox_t *mailbox_handle, int new_temp)
{
    if (mailbox_handle == NULL)
    	return pdFALSE; // Validación básica

    // 1. Espera a que el Buffer esté vacío (liberado por el receptor)
    osSemaphoreAcquire(mailbox_handle->BufferEmpty_Sem, osWaitForever);

    // 2. Adquiere Mutex (Exclusión Mutua)
    osMutexAcquire(mailbox_handle->Mailbox_Mutex, osWaitForever);

    // 3. Escribe el dato
    mailbox_handle->data = new_temp;

    // 4. Libera Mutex
    osMutexRelease(mailbox_handle->Mailbox_Mutex);

    // 5. Señala que hay un Dato Disponible (despierta al receptor)
    osSemaphoreRelease(mailbox_handle->DataAvailable_Sem);

    return pdTRUE;
}

int Mailbox_Pend(Mailbox_t *mailbox_handle)
{
    if (mailbox_handle == NULL) return -1; // Validación básica

    int read_temp;

    // 1. Espera a que haya un Dato Disponible (señalado por el remitente)
    osSemaphoreAcquire(mailbox_handle->DataAvailable_Sem, osWaitForever);

    // 2. Adquiere Mutex (Exclusión Mutua)
    osMutexAcquire(mailbox_handle->Mailbox_Mutex, osWaitForever);

    // 3. Lee el dato
    read_temp = mailbox_handle->data;

    // 4. Libera Mutex
    osMutexRelease(mailbox_handle->Mailbox_Mutex);

    // 5. Señala que el Buffer está Vacío (despierta al remitente)
    osSemaphoreRelease(mailbox_handle->BufferEmpty_Sem);

    return read_temp;
}
