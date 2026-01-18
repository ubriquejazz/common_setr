#include <stdio.h>
#include "../delay.h"
#include "../pool.h"

UART_HandleTypeDef huart2;
Pool_t FreqGreen, FreqRed;

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId OrangeTaskHandle;

int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(&huart2,(uint8_t *)ptr,len,10);
	return len;
}

void Pool_Test() {
	if (Pool_Init(&FreqGreen, 0) == pdTRUE)
    if (Pool_Escribir(&FreqGreen, HIG_FREQ) == pdTRUE)
      printf("GREEN value: %d", Pool_Leer(FreqGreen));
    else
      printf("GREEN: Cant write!");
    else
      printf("GREEN:No initialized!");

	if (Pool_Init(&FreqRed, 0) == pdTRUE)
    if (Pool_Escribir(&FreqRed, LOW_FREQ) == pdTRUE)
      printf("RED value: %d", Pool_Leer(FreqRed));
    else
      printf("RED: Cant write");
    else
      printf("RED:No initialized!");
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
