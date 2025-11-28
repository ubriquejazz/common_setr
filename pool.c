#include "pool.h"
#include "cmsis_os.h"

SemaphoreHandle_t xSemaphore;

void Pool_Init() {
    xSemaphore = xSemaphoreCreateBinary();
}

// xSemaphoreTake, xSemaphoreGive
// portMAX_DELAY = osWaitForever

int Pool_LeerFrecRojo() {
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    int retVal = PoolParpadeo.FrecLEDRojo;
    xSemaphoreGive(xSemaphore);
    return retVal;
}

int Pool_LeerFrecVerde() {
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    int retVal = PoolParpadeo.FrecLEDRojo;
    xSemaphoreGive(xSemaphore);
    return retVal;
}

void Pool_EscribirFrecRojo(int value) {
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    PoolParpadeo.FrecLEDRojo = value;
    xSemaphoreGive(xSemaphore);
}

void Pool_EscribirFrecVerde(int value) {
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    PoolParpadeo.FrecLEDVerde = value;
    xSemaphoreGive(xSemaphore);
}
