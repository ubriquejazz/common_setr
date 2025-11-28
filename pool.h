#ifndef POOL_H
#define POOL_H

typedef struct
{
    int FrecLEDVerde;
    int FrecLEDRojo;
}
FrecParpadeo;

FrecParpadeo PoolParpadeo = {10, 1}; // Valores iniciales

void Pool_Init()
bool Pool_EscribirFrecRojo(int);
bool Pool_EscribirFrecVerde(int);

int Pool_LeerFrecRojo();
int Pool_LeerFrecVerde();

#endif // POOL_H