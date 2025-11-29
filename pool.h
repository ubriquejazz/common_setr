#ifndef POOL_H
#define POOL_H

typedef struct
{
    int FrecLEDVerde;
    int FrecLEDRojo;
}
FrecParpadeo;

void Pool_Init();
void Pool_EscribirFrecRojo(int);
void Pool_EscribirFrecVerde(int);

int Pool_LeerFrecRojo();
int Pool_LeerFrecVerde();

#endif // POOL_H
