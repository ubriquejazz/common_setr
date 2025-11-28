
#include "pool.h"

SemaphoreHandle_t xSemaphore;

void Pool_Init() {
    xSemaphore = xSemaphoreCreateBinary();
}

// xSemaphoreTake, xSemaphoreGive
// porMAX_DELAY = osWaitForever

int Pool_LeerFrecRojo() {
    xSemaphoreTake(xSemaphore, porMAX_DELAY);
    int retVal = PoolParpadeo.FrecLEDRojo;
    xSemaphoreGive(xSemaphore);
    return retVal;
}

int Pool_LeerFrecVerde() {
    xSemaphoreTake(xSemaphore, porMAX_DELAY);
    int retVal = PoolParpadeo.FrecLEDRojo;
    xSemaphoreGive(xSemaphore);
    return retVal;
}

bool Pool_EscribirFrecRojo(int value) {
    xSemaphoreTake(xSemaphore, porMAX_DELAY);
    PoolParpadeo.FrecLEDRojo = value;
    xSemaphoreGive(xSemaphore);
    return true;
}

bool Pool_EscribirFrecVerde(int value) {
    xSemaphoreTake(xSemaphore, porMAX_DELAY);
    PoolParpadeo.FrecLEDVerde = value;
    xSemaphoreGive(xSemaphore);
    return true;
}