#ifndef CFLAG_H
#define CFLAG_H

#include "cmsis_os.h"

typedef enum {Set, Reset} CFlagState_t;

typedef struct {
    SemaphoreHandle_t semaphore;
    CFlagState_t flag_state; // 
} CFlag_t;

BaseType_t CFlag_Init(CFlag_t* handle);
BaseType_t CFlag_Set(CFlag_t* handle);
BaseType_t CFlag_Clear(CFlag_t* handle);
CFlagState_t CFlag_Wait(CFlag_t* handle);

#endif // CFLAG_H
