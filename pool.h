#ifndef POOL_H
#define POOL_H

#include "cmsis_os.h"

typedef struct {
    int data;
    int threshold;
} Pool_t;

BaseType_t Pool_Init(Pool_t* handle, int threshold);
BaseType_t Pool_Escribir(Pool_t* handle, int data);
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
