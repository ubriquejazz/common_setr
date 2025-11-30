// condition_flag.c

SemaphoreHandle_t xSemaphore;

CondFlag_T Condition;

bool CondFlag_Init() {
    bool retVal = pdTRUE;
    xSemaphore = xSemaphoreCreateMutex();
    if (xSemaphore == NULL)
        // insufficient heap memory
        retVal = pdFALSE;
    else {
        // 
        Condition = Reset;
    }
    return retVal;
}

bool CondFlag_Set() {
    bool retVal = pdFALSE;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        Condition = Set;
        xSemaphoreGive(xSemaphore);
        retVal = pdTRUE;
    }
}

bool CondFlag_Clear(CondFlag_T* flag_handle) {
    bool retVal = pdFALSE;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        Condition = Reset;
        xSemaphoreGive(xSemaphore);
        retVal = pdTRUE;
    }
}

CondFlag_T CondFlag_Check(const CondFlag_T* flag_handle) {
    CondFlag_T retVal = False;
    if ( xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        retVal = Condition;
        xSemaphoreGive(xSemaphore);
    }
    return retVal;
}