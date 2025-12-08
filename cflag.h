#ifndef CFLAG_H
#define CFLAG_H

#include "cmsis_os.h"

typedef enum {Set, Reset} CFLAGFlagState_T;

typedef struct {
    SemaphoreHandle_t semaphore;
    CFLAGFlagState_T state; // 
} CFLAGFlag_T;

BaseType_t CFLAGFlag_Init(CFLAGFlag_T* handle);
BaseType_t CFLAGFlag_Set(CFLAGFlag_T* handle);
BaseType_t CFLAGFlag_Clear(CFLAGFlag_T* handle);
BaseType_t CFLAGFlag_Wait(CFLAGFlag_T* handle);

#endif // CFLAG_H
