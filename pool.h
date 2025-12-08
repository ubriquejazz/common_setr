#ifndef POOL_H
#define POOL_H

#include "cmsis_os.h"

typedef struct {
    SemaphoreHandle_t semaphore;
    int data;
} Pool_t;

BaseType_t Pool_Init(Pool_t* handle);
BaseType_t Pool_Escribir(Pool_t* handle, int value);
int Pool_Leer(Pool_t* handle);

#if(0)
typedef struct
{
    int FrecLEDVerde;
    int FrecLEDRojo;
}
FrecParpadeo;

BaseType_t Pool_EscribirFrecRojo(int);
BaseType_t Pool_EscribirFrecVerde(int);

int Pool_LeerFrecRojo();
int Pool_LeerFrecVerde();
#endif 

#endif // POOL_H
