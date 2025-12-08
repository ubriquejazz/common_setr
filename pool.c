#include "pool.h"
#include "delay.h"

BaseType_t Pool_Init(Pool_t* handle) {
    BaseType_t retVal = pdTRUE;
    handle->sempahore = xSemaphoreCreateBinary();
    if (handle->semaphore == NULL)
        // insufficient heap memory
        retVal = pdFALSE;
    else {
        handle->data = FLASH_LOW_FREQ;
        //PoolParpadeo.FrecLEDVerde = FLASH_LOW_FREQ;
        //PoolParpadeo.FrecLEDRojo = FLASH_HIGH_FREQ;
    }
    return retVal;
}

BaseType_t Pool_Escribir(Pool_t* handle, int value) {
    BaseType_t retVal = pdFALSE;
    if ( xSemaphoreTake(Pool_Semph, portMAX_DELAY) == pdTRUE) {
        handle->data = value;
        xSemaphoreGive(Pool_Semph);
        retVal = pdTRUE;
    }
    return retVal;
}

int Pool_Leer(Pool_t* handle) {
    int retVal = -1;
    if ( xSemaphoreTake(handle->semaphore, portMAX_DELAY) == pdTRUE) {
        retVal = handle->data;
        xSemaphoreGive(Pool_Semph);
    }
    return retVal;
}

#if(0)

SemaphoreHandle_t Pool_Semph;
FrecParpadeo PoolParpadeo;

int Pool_LeerFrecRojo() {
    int retVal = -1;
    if ( xSemaphoreTake(Pool_Semph, portMAX_DELAY) == pdTRUE) {
        retVal = PoolParpadeo.FrecLEDRojo;
        xSemaphoreGive(Pool_Semph);
    }
    return retVal;
}

int Pool_LeerFrecVerde() {
    int retVal = -1;
    if ( xSemaphoreTake(Pool_Semph, portMAX_DELAY) == pdTRUE) {
        retVal = PoolParpadeo.FrecLEDVerde;
        xSemaphoreGive(Pool_Semph);
    }
    return retVal;
}


BaseType_t Pool_EscribirFrecRojo(int value) {
    BaseType_t retVal = pdFALSE;
    if ( xSemaphoreTake(Pool_Semph, portMAX_DELAY) == pdTRUE) {
        PoolParpadeo.FrecLEDRojo = value;
        xSemaphoreGive(Pool_Semph);
        retVal = pdTRUE;
    }
    return retVal;
}

BaseType_t Pool_EscribirFrecVerde(int value) {
    BaseType_t retVal = pdFALSE;
    if ( xSemaphoreTake(Pool_Semph, portMAX_DELAY) == pdTRUE) {
        PoolParpadeo.FrecLEDVerde = value;
        xSemaphoreGive(Pool_Semph);
        retVal = pdTRUE;
    }
    return retVal;
}

#endif