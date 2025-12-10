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

#endif // POOL_H
