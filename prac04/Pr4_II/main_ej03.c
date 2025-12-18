#include "../delay.h"
#include "../pool.h"
#include <stdio.h>		// for sprintf
#include <string.h>		// for strlen

UART_HandleTypeDef huart2;

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId OrangeTaskHandle;

char uart_msg[50];

void print_uart_msg() {
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_msg, strlen(uart_msg), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
}

void Pool_Test() {
	if (Pool_Init(&FreqGreen, 0) == pdTRUE)
	if (Pool_Escribir(&FreqGreen, HIG_FREQ) == pdTRUE)
		sprintf(uart_msg, "GREEN value: %d", Pool_Leer(FreqGreen));
	else
		sprintf(uart_msg, "GREEN: Cant write!");
	else
	  sprintf(uart_msg, "GREEN:No initialized!");
	print_uart_msg();

	if (Pool_Init(&FreqRed, 0) == pdTRUE)
	if (Pool_Escribir(&FreqRed, LOW_FREQ) == pdTRUE)
		sprintf(uart_msg, "RED value: %d", Pool_Leer(FreqRed));
	else
		sprintf(uart_msg, "RED: Cant write");
	else
	  sprintf(uart_msg, "RED:No initialized!");
	print_uart_msg();
}

void main() {
    // ...
    Pool_Test();

}

void StartCtrl() {
  int duracion_ms = 8000;
  for(;;)
  {
        Pool_Escribir(&FreqRed, HIG_FREQ);
        Pool_Escribir(&FreqGreen, LOW_FREQ);
        NonBlocking_Freq(PIN_ORANGE, duracion_ms, LOW_FREQ);

        Pool_Escribir(&FreqRed, LOW_FREQ);
        Pool_Escribir(&FreqGreen, HIG_FREQ);
        NonBlocking_Freq(PIN_ORANGE, duracion_ms, LOW_FREQ);
  }
}

void StartGreen(void const * argument) {
    int duracion_ms = 9500;
    for(;;)
    {
        Blocking_Freq(PIN_GREEN, duracion_ms, Pool_Leer(FreqGreen));
		// osDelay(9500);
    }
}

void StartRed(void const * argument) {
    int duracion_ms = 5500;
    for(;;)
    {
        Blocking_Freq(PIN_RED, duracion_ms, Pool_Leer(FreqRed));
        //osDelay(6000);
    }
}
