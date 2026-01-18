#ifndef CFLAG_H
#define CFLAG_H

#include "cmsis_os.h"

typedef enum {SET, CLR} CFlagState_t;

typedef struct {
    int data;
    CFlagState_t state;
} CFlag_t;

BaseType_t CFlag_Init(CFlag_t* handle);

void CFlag_Set(CFlag_t* handle, int value);
void CFlag_Wait(CFlag_t* handle);
int CFlag_Get(CFlag_t* handle);

#endif // CFLAG_H
