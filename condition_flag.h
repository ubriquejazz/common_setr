#ifndef COND_H
#define COND_H

#include <stdint.h>

typedef enum {Set, Reset} CondFlag_T;

typedef Base bool;

bool CondFlag_Init();
CondFlag_T Cond_Check();
bool CondFlag_Set();
bool CondFlag_Clear();

#endif // COND_H
