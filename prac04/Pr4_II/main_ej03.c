# include "pool.h"

UART_HandleTypeDef huart2;

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId OrangeTaskHandle;

#if(0)
osMutexId myMutexHandle;
osSemaphoreId mySemHandle;
#else
Pool_t FreqRed;
Pool_t FreqGreen;
#endif

void println(const char *msg) {
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
}

void main() {
    // ...
    Pool_Init(&FreqGreen);
    Pool_Init(&FreqRed);

}

void StartCtrl() {
    // Cambio de parpadeo  del LED verde a 1Hz 
    // Cambio de parpadeo  del LED rojo a 10Hz 
    Pool_Escribir(&FreqRed, 10);
    Pool_Escribir(&FreqGreen, 1);
    osDelay(8000);

    // Cambio de parpadeo  del LED verde a 10Hz 
    // Cambio de parpadeo  del LED rojo a 1Hz 

    Pool_Escribir(&FreqRed, 1);
    // Pool_EscribirFrecRojo(1);

    Pool_Escribir(&FreqGreen, 10);
    // Pool_EscribirFrecVerde(10);
    osDelay(8000);
}

void StartGreen(void const * argument) {
    int freq=0;
    char msg[50];
    for(;;)
    {
    sprintf(msg, "Green: %d", freq); println(msg);
    //Blocking_Freq(PIN_GREEN, 10000, freq);
    freq = Pool_Leer(&FreqGreen); // Pool_LeerFrecVerde();
    osDelay(9500);
    }
}

void StartRed(void const * argument) {
    int freq=99;
    char msg[50];
    for(;;)
    {
    sprintf(msg, "Rojo: %d", freq); println(msg);
    freq = Pool_Leer(&FreqRed); 
    osDelay(6000);
    }
}
