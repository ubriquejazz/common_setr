// pool.c used in prac04B/ej03.c

#include "pool.h"
#include "delay.h"

SemaphoreHandle_t miSemaforo = NULL;

BaseType_t Pool_Init(Pool_t* handle, int threshold) {

    BaseType_t retVal = pdTRUE;
    miSemaforo= xSemaphoreCreateBinary();
    if (miSemaforo== NULL)
        // insufficient heap memory
        retVal = pdFALSE;
    else {
        handle->data = 0;
        handle->threshold = threshold;
        xSemaphoreGive(miSemaforo);
    }
    return retVal;
}

BaseType_t Pool_Escribir(Pool_t* handle, int data) {
    if (handle == NULL)
    	return pdFALSE; // Validación básica

    BaseType_t retVal = pdFALSE;
    if ( xSemaphoreTake(miSemaforo, portMAX_DELAY) == pdTRUE) {
        handle->data = data;
        xSemaphoreGive(miSemaforo);
        retVal = pdTRUE;
    }
    return retVal;
}

int Pool_Leer(Pool_t handle) {
    int retVal = -1;

    if ( xSemaphoreTake(miSemaforo, portMAX_DELAY) == pdTRUE) {
        retVal = handle.data;
        xSemaphoreGive(miSemaforo);
    }
    return retVal;
}