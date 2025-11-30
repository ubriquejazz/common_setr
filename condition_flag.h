#ifndef COND_H
#define COND_H

#include "cmsis_os.h"

typedef enum {Set, Reset} CondFlag_T;

BaseType_t CondFlag_Init();
CondFlag_T Cond_Check();
BaseType_t CondFlag_Set();
BaseType_t CondFlag_Clear();

#endif // COND_H
