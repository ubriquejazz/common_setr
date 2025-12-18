#include "../delay.h"
#include "../cflag.h"

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId BlueTaskHandle;

CFlag_t Flag1, Flag2;
char huart2_msg[50];

void print_msg() {
	HAL_UART_Transmit(&huart2, (uint8_t *)huart2_msg, strlen(huart2_msg), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
}

void CFlag_Test() {
	if (CFlag_Init(&Flag1) == pdTRUE)
	if (CFlag_Set(&Flag1) == pdTRUE)
		sprintf(huart2_msg, "Flag1 value: %d", Flag1.data);
	else
		sprintf(huart2_msg, "Flag1: Cant write!");
	else
	  sprintf(huart2_msg, "Flag1: No initialized!");
	print_msg();

	if (CFlag_Init(&Flag2) == pdTRUE)
	if (CFlag_Set(&Flag2) == pdTRUE)
		sprintf(huart2_msg, "Flag2 value: %d", Flag2.data);
	else
		sprintf(huart2_msg, "Flag2: Cant write!");
	else
	  sprintf(huart2_msg, "Flag2: No initialized!");
	print_msg();
}

void main() {

  MX_GPIO_Init();
  Cflag_Test();

}

void StartRed(void const * argument)
{
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);
		osSignalWait(Flag1);
    NonBlocking_Freq(PIN_RED, 5000, HIG_FREQ);
    vTaskSuspend(NULL);
  }
}

void StartGreen(void const * argument)
{
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
		osSignalWait(Flag2);
    NonBlocking_Freq(PIN_GREEN, 5000, HIG_FREQ);
    vTaskSuspend(NULL);
  }
  
}

void StartBlue(void const * argument)
{
  int delay = 100;
  CFlagState_t aux1, aux2;

  for(;;)
  {
    NonBlocking_Freq(PIN_BLUE, 10000, LOW_FREQ);
    HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET);

    osSignalSet(Flag1, 1);
    HAL_Delay(6000);
    
		osSignalSet(Flag2, 1);
    HAL_Delay(6000);

  }
}