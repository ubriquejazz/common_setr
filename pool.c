#include "pool.h"
#include "delay.h"
#include "cmsis_os.h"

SemaphoreHandle_t xSemaphore;

FrecParpadeo PoolParpadeo;

bool Pool_Init() {
    bool retVal = pdTRUE;
    xSemaphore = xSemaphoreCreateBinary();
    if (xSemaphore == NULL)
        // insufficient heap memory
        retVal = pdFALSE;
    else {
        PoolParpadeo.FrecLEDVerde = FLASH_LOW_FREQ;
        PoolParpadeo.FrecLEDRojo = FLASH_HIGH_FREQ;
    }
    return retVal;
}

// xSemaphoreTake, xSemaphoreGive
// portMAX_DELAY = osWaitForever

int Pool_LeerFrecRojo() {
    int retVal = -1;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        retVal = PoolParpadeo.FrecLEDRojo;
        xSemaphoreGive(xSemaphore);
    }
    return retVal;
}

int Pool_LeerFrecVerde() {
    int retVal = -1;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        retVal = PoolParpadeo.FrecLEDVerde;
        xSemaphoreGive(xSemaphore);
    }
    return retVal;
}

void Pool_EscribirFrecRojo(int value) {
    bool retVal = pdFALSE;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        PoolParpadeo.FrecLEDRojo = value;
        xSemaphoreGive(xSemaphore);
        retVal = pdTRUE;
    }
    return retVal;
}

void Pool_EscribirFrecVerde(int value) {
    bool retVal = pdFALSE;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        PoolParpadeo.FrecLEDVerde = value;
        xSemaphoreGive(xSemaphore);
        retVal = pdTRUE;
    }
    return retVal;
}
