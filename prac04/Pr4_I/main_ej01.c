#include "../delay.h"
#include "../cflag.h"

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId BlueTaskHandle;

CFlag_t Flag1, Flag2;
UART_HandleTypeDef huart2;

int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(&huart2,(uint8_t *)ptr,len,10);
	return len;
}

void fatal_error(const char* string) {
	printf("[Error] %s", string);
	HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET);
	vTaskSuspend(NULL);
}

void main() {

  MX_GPIO_Init();
  MX_UART_Init(&uart2);

  if (CFlag_Init(&Flag1) != pdTRUE)
	  fatal_error("Flag1");

  if (CFlag_Init(&Flag2) != pdTRUE)
	  fatal_error("Flag2");
  
}

void StartRed(void const * argument)
{
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);
		CFlag_Wait(Flag1);
    NonBlocking_Freq(PIN_RED, 5000, HIG_FREQ);
    vTaskSuspend(NULL);
  }
}

void StartGreen(void const * argument)
{
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
		CFlag_Wait(Flag2);
    NonBlocking_Freq(PIN_GREEN, 5000, HIG_FREQ);
    vTaskSuspend(NULL);
  }
}

void StartBlue(void const * argument)
{
  for(;;)
  {
    NonBlocking_Freq(PIN_BLUE, 10000, LOW_FREQ);
    HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET);
    CFlag_Set(&Flag1, 1);
		HAL_Delay(6000);
		CFlag_Set(&Flag2, 1);
    HAL_Delay(6000);
  }
}