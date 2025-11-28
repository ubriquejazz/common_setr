
semaphore Azul2Verde, Azul2Rojo


void StartRed() {

    osSemaphoreWait(Azul2Rojo, portMAX_DELAY);
    Blocking_Freq(PIN_RED, 5000, 10);
}

void StartGreen() {

    osSemaphoreWait(Azul2Verde, portMAX_DELAY);
    Blocking_Freq(PIN_GREEN, 5000, 10);
}
