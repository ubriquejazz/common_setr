#include "../delay.h"

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId BlueTaskHandle;

void main() {
  MX_GPIO_Init();
}

// Tarea receptora (wait)
void StartRed(void const * argument)
{
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);
		osSignalWait(1, osWaitForever);
		NonBlocking_Freq(PIN_RED, 5000, HIG_FREQ);
  }
}

// Tarea receptora (wait)
void StartGreen(void const * argument)
{
  for(;;)
  {
	  HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
    osSignalWait(1, osWaitForever);
    NonBlocking_Freq(PIN_GREEN, 5000, HIG_FREQ);
  }
}


void StartBlue(void const * argument)
{
  /* USER CODE BEGIN StartRed */
  /* Infinite loop */ 
  for(;;)
  {
    NonBlocking_Freq(PIN_BLUE, 10000, LOW_FREQ);
    HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET);

    osSignalSet(GreenTaskHandle, 1);
    HAL_Delay(6000);
    
		osSignalSet(RedTaskHandle, 1);
    HAL_Delay(6000);
  }
}