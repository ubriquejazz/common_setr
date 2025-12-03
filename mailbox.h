#ifndef MAILBOX_H
#define MAILBOX_H

#include "cmsis_os.h"

typedef enum {Set, Reset} MBox_T;

BaseType_t MBox_Init(MBox_T* handle);
BaseType_t MBox_Set(MBox_T* handle);
BaseType_t MBox_Clear(MBox_T* handle);

#endif