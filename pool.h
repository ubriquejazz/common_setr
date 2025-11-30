#ifndef POOL_H
#define POOL_H

#include "cmsis_os.h"

typedef struct
{
    int FrecLEDVerde;
    int FrecLEDRojo;
}
FrecParpadeo;

BaseType_t Pool_Init();
BaseType_t Pool_EscribirFrecRojo(int);
BaseType_t Pool_EscribirFrecVerde(int);

int Pool_LeerFrecRojo();
int Pool_LeerFrecVerde();

#endif // POOL_H
