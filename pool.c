#include "pool.h"
#include "delay.h"

SemaphoreHandle_t xSemaphore;

FrecParpadeo PoolParpadeo;

BaseType_t Pool_Init() {
    BaseType_t retVal = pdTRUE;
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

BaseType_t Pool_EscribirFrecRojo(int value) {
    BaseType_t retVal = pdFALSE;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        PoolParpadeo.FrecLEDRojo = value;
        xSemaphoreGive(xSemaphore);
        retVal = pdTRUE;
    }
    return retVal;
}

BaseType_t Pool_EscribirFrecVerde(int value) {
    BaseType_t retVal = pdFALSE;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        PoolParpadeo.FrecLEDVerde = value;
        xSemaphoreGive(xSemaphore);
        retVal = pdTRUE;
    }
    return retVal;
}
