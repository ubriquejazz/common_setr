#include "delay.h"

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId BlueTaskHandle;

void main() {
  MX_GPIO_Init();
}

// Tarea receptoras
void StartRed(void const * argument)
{
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);
		osSignalWait(1, osWaitForever);
		Blocking_Freq(PIN_RED, 5000, FLASH_HIGH_FREQ);
  }
}

void StartGreen(void const * argument)
{

  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
	  HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
    osSignalWait(0x0001, osWaitForever);
    Blocking_Freq(PIN_GREEN, 5000, FLASH_HIGH_FREQ);
  }
}

void StartBlue(void const * argument)
{
  /* USER CODE BEGIN StartRed */
  /* Infinite loop */ 
  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {

    HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET);
    Blocking_Freq(PIN_BLUE, 10000, FLASH_LOW_FREQ);

    osSignalSet(GreenTaskHandle, 1);
    //Blocking_Freq(PIN_BLUE, 6000, FLASH_HIGH_FREQ);
    HAL_Delay(6000);

		osSignalSet(RedTaskHandle, 1);
		Blocking_Freq(PIN_BLUE, 6000, FLASH_HIGH_FREQ);
		//HAL_Delay(6000);

  }
}