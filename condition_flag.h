#ifndef COND_H
#define COND_H

#include "cmsis_os.h"

typedef enum {Set, Reset} CondFlagState_T;

typedef struct {
    SemaphoreHandle_t semaphore;
    CondFlagState_T state; // 
} CondFlag_T;

BaseType_t CondFlag_Init(CondFlag_T* handle);
BaseType_t CondFlag_Set(CondFlag_T* handle);
BaseType_t CondFlag_Clear(CondFlag_T* handle);
BaseType_t CondFlag_Wait(CondFlag_T* handle);

#endif // COND_H
