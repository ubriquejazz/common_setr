// mailbox.c used in prac05/main.c

#include "mailbox.h"

SemaphoreHandle_t Mailbox_Mutex;
SemaphoreHandle_t DataAvailable_Sem;    // producer
SemaphoreHandle_t BufferEmpty_Sem;      // consumer

BaseType_t Mailbox_Init(Mailbox_t* handle, int tipo) {
	BaseType_t retVal = pdTRUE;

    Mailbox_Mutex = xSemaphoreCreateBinary();
    DataAvailable_Sem = xSemaphoreCreateBinary();
    BufferEmpty_Sem = xSemaphoreCreateBinary();
    
    if ( Mailbox_Mutex == NULL || DataAvailable_Sem == NULL || 
         BufferEmpty_Sem == NULL)  {
        retVal = pdFALSE;
    }
    handle->threshold = tipo;
    handle->data = 0;

    // BufferEmpty_Sem, Mailbox_Mutex = 1
    xSemaphoreGive(BufferEmpty_Sem);
    xSemaphoreGive(Mailbox_Mutex);
    return retVal;
}

BaseType_t Mailbox_Post(Mailbox_t *handle, int new_data)
{
    if (handle == NULL)
    	return pdFALSE; // Validación básica

    // Espera a que el Buffer esté vacío (liberado por el receptor)
    xSemaphoreTake(BufferEmpty_Sem, portMAX_DELAY);

        if ( xSemaphoreTake(Mailbox_Mutex, portMAX_DELAY) == pdTRUE) {
            handle->data = new_data;
            xSemaphoreGive(Mailbox_Mutex);
        }

    // Señala que hay un Dato Disponible (despierta al receptor)
    xSemaphoreGive(DataAvailable_Sem);
    return pdTRUE;
}

int Mailbox_Pend(Mailbox_t *handle)
{
    int value = -1;
    if (handle == NULL) 
        return value; // Validación básica

    // Espera a que haya un Dato Disponible (señalado por el remitente)
    xSemaphoreTake(DataAvailable_Sem, portMAX_DELAY);
       
        if ( xSemaphoreTake(Mailbox_Mutex, portMAX_DELAY) == pdTRUE) {
            value = handle->data;
            xSemaphoreGive(Mailbox_Mutex);
        }

    // Señala que el Buffer está Vacío (despierta al remitente)
    xSemaphoreGive(BufferEmpty_Sem);
    return value;
}
