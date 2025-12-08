#ifndef MAILBOX_H
#define MAILBOX_H

#include "cmsis_os.h"

typedef struct {
    int data;
    osMutexId Mailbox_Mutex;
    osSemaphoreId DataAvailable_Sem;
    osSemaphoreId BufferEmpty_Sem;
} Mailbox_t;

BaseType_t Mailbox_Init(Mailbox_t* handle);
int Mailbox_Pend(Mailbox_t* handle); // Tarea receptora (Monitoreo)
BaseType_t Mailbox_Post(Mailbox_t* handle, int new_temp); // Tarea remitente (Adquisicion)

#endif
