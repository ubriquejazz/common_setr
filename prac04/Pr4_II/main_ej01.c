
semaphore Azul2Verde, Azul2Rojo


void StartRed() {

    osSemaphoreWait(Azul2Rojo, portMAX_DELAY);
    Blocking_Freq(PIN_RED, 5000, 10);
}

void StartGreen() {

    osSemaphoreWait(Azul2Verde, portMAX_DELAY);
    Blocking_Freq(PIN_GREEN, 5000, 10);
}

void StartBlue() {

    // Parpadeo de 1Hz durante 10s
    Blocking_Freq(PIN_BLUE, 10000, 1);

    // Set del semaforo
    osSemaphoreRelease(Azul2Verde);
    osDelay(6000);

    // Set del semaforo
    osSemaphoreRelease(Azul2Rojo);
    osDelay(6000);

}