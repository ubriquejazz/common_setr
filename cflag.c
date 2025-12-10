#include "main.h"
#include "cflag.h"

BaseType_t CFlag_Init(CFlag_t* handle) {
	BaseType_t retVal = pdTRUE;
    handle->semaphore = xSemaphoreCreateBinary();
    if (handle->semaphore == NULL)
        // insufficient heap memory
        retVal = pdFALSE;
    else {
        handle->flag_state = Reset;
    }
    return retVal;
}

// Sets the flag and gives the semaphore, unblocking a waiting task
BaseType_t CFlag_Set(CFlag_t* handle) {
	BaseType_t retVal = pdTRUE;
    if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
        xSemaphoreGive(handle->semaphore);
    } else {
        // If the scheduler hasn't started
        retVal = pdFALSE;
    }
    handle->flag_state = Set;
    return retVal;
}

// Clears the flag and gives the semaphore, unblocking ...
BaseType_t CFlag_Clear(CFlag_t* handle) {
 	BaseType_t retVal = pdTRUE;
    if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
        xSemaphoreGive(handle->semaphore);
    } else {
        // If the scheduler hasn't started
        retVal = pdFALSE;
    }
    handle->flag_state = Reset;
    return retVal;
}
   
// Waits for the flag to be set (takes the semaphore).
CFlagState_t CFlag_Wait(CFlag_t* flag) {
    xSemaphoreTake(flag->semaphore, portMAX_DELAY);
    return flag->flag_state;
}
