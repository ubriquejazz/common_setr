// cflag.c used in prac04A/main_ej01.c
#include "cflag.h"

static SemaphoreHandle_t miSemaforo;

BaseType_t CFlag_Init(CFlag_t* handle) {
	BaseType_t retVal = pdTRUE;
    miSemaforo = xSemaphoreCreateBinary();
    if (miSemaforo == NULL)
        // insufficient heap memory
        retVal = pdFALSE;
    else {
        handle->state = Reset;
        xSemaphoreGive(miSemaforo);
    }
    return retVal;
}

// Sets the flag and gives the semaphore, unblocking a waiting task
void CFlag_Set(CFlag_t* handle, int value) {
	handle->state = Set;
	handle->data = value;
	xSemaphoreGive(miSemaforo);
}

// Waits for the flag to be set (takes the semaphore).
void CFlag_Wait(CFlag_t flag) {
	xSemaphoreTake(miSemaforo, portMAX_DELAY);
}

