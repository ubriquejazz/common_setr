#ifndef COND_H
#define COND_H

#include "cmsis_os.h"

typedef enum {Set, Reset} CondFlag_T;

BaseType_t CondFlag_Init(CondFlag_T* flag_handle);
BaseType_t CondFlag_Set(CondFlag_T* flag_handle);
BaseType_t CondFlag_Clear(CondFlag_T* flag_handle);

#endif // COND_H
