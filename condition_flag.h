#ifndef COND_H
#define COND_H

#include <stdint.h>

typedef enum {Set, Reset} CondFlag_T;

CondFlag_T* CondFlag_Create()
CondFlag_T Cond_Check();
void CondFlag_Set(CondFlag_T* flag_handle);
void CondFlag_Clear(CondFlag_T* flag_handle);

#endif // COND_H
