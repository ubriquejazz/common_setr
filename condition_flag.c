#include "main.h"
#include "condition_flag.h"

SemaphoreHandle_t InternSemph;

BaseType_t CondFlag_Init(CondFlag_T* flag_handle) {
	BaseType_t retVal = pdTRUE;
    InternSemph = xSemaphoreCreateMutex();
    if (InternSemph == NULL)
        // insufficient heap memory
        retVal = pdFALSE;
    else {
        // Init value
    	*flag_handle = Reset;
    }
    return retVal;
}

BaseType_t CondFlag_Set(CondFlag_T* flag_handle) {
	BaseType_t retVal = pdFALSE;
    if ( xSemaphoreTake(InternSemph, portMAX_DELAY) == pdTRUE) {
    	*flag_handle = Set;
        xSemaphoreGive(InternSemph);
        retVal = pdTRUE;
    }
    return retVal;
}

BaseType_t CondFlag_Clear(CondFlag_T* flag_handle) {
	BaseType_t retVal = pdFALSE;
    if ( xSemaphoreTake(InternSemph, portMAX_DELAY) == pdTRUE) {
        *flag_handle = Reset;
        xSemaphoreGive(InternSemph);
        retVal = pdTRUE;
    }
    return retVal;
}
