#ifndef CFLAG_H
#define CFLAG_H

#include "cmsis_os.h"

typedef enum {Unlock, Locked, Error} CFlagState_t;

typedef struct {
    int data;
    CFlagState_t state;
} CFlag_t;

BaseType_t CFlag_Init(CFlag_t* handle);

void CFlag_Set(CFlag_t* handle, int value);
void CFlag_Wait(CFlag_t);

#endif // CFLAG_H
