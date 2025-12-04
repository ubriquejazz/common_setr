#include "main.h"
#include "condition_flag.h"

BaseType_t CondFlag_Init(CondFlag_T* flag_handle) {
	BaseType_t retVal = pdTRUE;

    flag_handle->semaphore = xSemaphoreCreateBinary();
    if (lag_handle->semaphore == NULL)
        // insufficient heap memory
        retVal = pdFALSE;
    else {
        flag_handle->state = Reset;
    }
    return retVal;
}

// Sets the flag and gives the semaphore, unblocking a waiting task
BaseType_t CondFlag_Set(CondFlag_T* flag_handle) {
	BaseType_t retVal = pdTRUE;
    if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
        xSemaphoreGive(flag_handle->semaphore);
    } else {
        // If the scheduler hasn't started
        retVal = pdFALSE;
    }
    flag_handle->state = Set;
    return retVal;
}

// Clears the flag and gives the semaphore, unblocking ...
BaseType_t CondFlag_Clear(CondFlag_T* flag_handle) {
 	BaseType_t retVal = pdTRUE;
    if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
        xSemaphoreGive(flag_handle->semaphore);
    } else {
        // If the scheduler hasn't started
        retVal = pdFALSE;
    }
    flag_handle->state = Reset;
    return retVal;
}
   
// Waits for the flag to be set (takes the semaphore).
BaseType_t CondFlag_Wait(CondFlag_T flag) {
	BaseType_t retVal;
    retVal = xSemaphoreTake(flag->semaphore, portMAX_DELAY);
    if ( retVal == pdTRUE) {
        
    }
    return retVal;
}
