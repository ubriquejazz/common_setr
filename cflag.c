#include "cflag.h"
#include "main.h"

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
BaseType_t CFlag_Set(CFlag_t* handle) {
    if (handle == NULL)
    	return pdFALSE; // Validación básica

	BaseType_t retVal = pdTRUE;
    // (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
    if (xSemaphoreTake(miSemaforo, portMAX_DELAY) == pdTRUE) {
        handle->state = Set;
        xSemaphoreGive(miSemaforo);
    } else {
        // If the scheduler hasn't started
        retVal = pdFALSE;
    }
    return retVal;
}

// Clears the flag and gives the semaphore, unblocking ...
BaseType_t CFlag_Clear(CFlag_t* handle) {
    if (handle == NULL)
    	return pdFALSE; // Validación básica

 	BaseType_t retVal = pdTRUE;
    // (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
    if ( xSemaphoreTake(miSemaforo, portMAX_DELAY) == pdTRUE) {
        handle->state = Reset;
        xSemaphoreGive(miSemaforo);
    } else {
        // If the scheduler hasn't started
        retVal = pdFALSE;
    }
    return retVal;
}
   
// Waits for the flag to be set (takes the semaphore).
CFlagState_t CFlag_Wait(CFlag_t* handle) {
    if (handle == NULL)
    	return Error; // Validación básica
    return handle->state;
}
