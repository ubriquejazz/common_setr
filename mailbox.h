#ifndef MAILBOX_H
#define MAILBOX_H

#include "cmsis_os.h"

typedef struct {
    int temperature_data;
    osMutexId Mailbox_Mutex;
    osSemaphoreId DataAvailable_Sem;
    osSemaphoreId BufferEmpty_Sem;
} Mailbox_t;

BaseType_t Mailbox_Init(MBox_T* handle);
int Mailbox_Pend(MBox_T* handle); // Tarea receptora (Monitoreo)
BaseType_t Mailbox_Post((MBox_T* handle, int new_temp); // Tarea remitente (Adquisicion)

#endif