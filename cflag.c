// cflag.c used in prac04A/main_ej01.c
#include "cflag.h"

SemaphoreHandle_t miSemaforo;

BaseType_t CFlag_Init(CFlag_t* handle) {
	BaseType_t retVal = pdTRUE;
    miSemaforo = xSemaphoreCreateBinary();
    if (miSemaforo == NULL)
        // insufficient heap memory
        retVal = pdFALSE;
    else {
        handle->state = CLR;
        handle->data = 0;
    }
    return retVal;
}

// Sets the flag and gives the semaphore, unblocking a waiting task
void CFlag_Set(CFlag_t* handle, int value) {
	handle->state = SET;
	handle->data = value;
	xSemaphoreGive(miSemaforo);
}

void CFlag_Wait(CFlag_t* handle) {
    if (handle->state == CLR) {
	    xSemaphoreTake(miSemaforo, portMAX_DELAY);
    }
    else {
        handle->state = CLR;
    }
}

// Cuando el estado es CLR, la tara queda suspendida.
// Si es SET, resetea el valor de la bandera y continua su ejecución.
int CFlag_Get(CFlag_t* handle) {
    int retVal = 0;
    if (handle->state == CLR) {
	    xSemaphoreTake(miSemaforo, portMAX_DELAY);
    }
    else {
        retVal = 1;
        handle->state = CLR;
    }
    return retVal
}

