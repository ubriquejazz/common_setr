#ifndef MAILBOX_H
#define MAILBOX_H

#include "cmsis_os.h"

typedef struct {
    int data;           // Valor del dato
    int threshold;      // Alarma
} Mailbox_t;

BaseType_t Mailbox_Init(Mailbox_t* handle, int threshold);

BaseType_t Mailbox_Post(Mailbox_t* handle, int new_data); // Tarea de adquisicion

int Mailbox_Pend(Mailbox_t* handle); // Tarea de monitoreo (receptora)

#endif
