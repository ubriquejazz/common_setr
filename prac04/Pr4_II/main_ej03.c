# include "pool.h"

UART_HandleTypeDef huart2;

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId OrangeTaskHandle;

char huart2_msg[50];

void print_msg() {
	HAL_UART_Transmit(&huart2, (uint8_t *)huart2_msg, strlen(huart2_msg), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
}

void Pool_Test() {
	if (Pool_Init(&FreqGreen, 0) == pdTRUE)
	if (Pool_Escribir(&FreqGreen, HIG_FREQ) == pdTRUE)
		sprintf(huart2_msg, "Pool value: %d", Pool_Leer(FreqGreen));
	else
		sprintf(huart2_msg, "Cant write");
	else
	  sprintf(huart2_msg, "No pool, no summer!");
	print_msg();

	if (Pool_Init(&FreqRed, 0) == pdTRUE)
	if (Pool_Escribir(&FreqRed, LOW_FREQ) == pdTRUE)
		sprintf(huart2_msg, "Pool value: %d", Pool_Leer(FreqRed));
	else
		sprintf(huart2_msg, "Cant write");
	else
	  sprintf(huart2_msg, "No pool, no summer!");
	print_msg();
}

void main() {
    // ...
    Pool_Test();

}

void StartCtrl() {
  for(;;)
  {
	    Pool_Escribir(&FreqRed, HIG_FREQ);
	    Pool_Escribir(&FreqGreen, LOW_FREQ);
	    osDelay(8000);

	    Pool_Escribir(&FreqRed, LOW_FREQ);
	    Pool_Escribir(&FreqGreen, HIG_FREQ);
	    osDelay(8000);
  }
}

void StartGreen(void const * argument) {
    int delay_ms = 9500;
    for(;;)
    {

		osDelay(9500);
    }
}

void StartRed(void const * argument) {
    int delay_ms = 5500;
    for(;;)
    {
        osDelay(6000);
    }
}
