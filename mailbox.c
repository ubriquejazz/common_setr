#include "mailbox.h"
#include "delay.h"

SemaphoreHandle_t Read_Semph, Write_Semph;
SemaphoreHandle_t InternSemph;

BaseType_t Mbox_Init(CondFlag_T* flag_handle) {
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

