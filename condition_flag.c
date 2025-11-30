#include "main.h"
#include "condition_flag.h"

SemaphoreHandle_t xSemaphore;

CondFlag_T Condition;

BaseType_t CondFlag_Init() {
	BaseType_t retVal = pdTRUE;
    xSemaphore = xSemaphoreCreateMutex();
    if (xSemaphore == NULL)
        // insufficient heap memory
        retVal = pdFALSE;
    else {
        // 
        Condition = Reset;
    }
    return retVal;
}

BaseType_t CondFlag_Set() {
	BaseType_t retVal = pdFALSE;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        Condition = Set;
        xSemaphoreGive(xSemaphore);
        retVal = pdTRUE;
    }
    return retVal;
}

BaseType_t CondFlag_Clear(CondFlag_T* flag_handle) {
	BaseType_t retVal = pdFALSE;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        Condition = Reset;
        xSemaphoreGive(xSemaphore);
        retVal = pdTRUE;
    }
    return retVal;
}

CondFlag_T CondFlag_Check(const CondFlag_T* flag_handle) {
    CondFlag_T retVal = Reset;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        retVal = Condition;
        xSemaphoreGive(xSemaphore);
    }
    return retVal;
}
