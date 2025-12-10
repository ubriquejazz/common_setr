# include "pool.h"

UART_HandleTypeDef huart2;

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId OrangeTaskHandle;

Pool_t FreqRed;
Pool_t FreqGreen;

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
  for(;;)
  {
	    Pool_Escribir(&FreqRed, FLASH_HIGH_FREQ);
	    Pool_Escribir(&FreqGreen, FLASH_LOW_FREQ);
	    osDelay(8000);

	    Pool_Escribir(&FreqRed, FLASH_LOW_FREQ);
	    Pool_Escribir(&FreqGreen, FLASH_HIGH_FREQ);
	    osDelay(8000);
  }
}

void StartGreen(void const * argument) {
    int freq=0;
    char msg[50];
    for(;;)
    {
        sprintf(msg, "Green: %d", freq); println(msg);
		freq = Pool_Leer(&FreqGreen);
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
