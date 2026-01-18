#include <stdio.h>
#include "../delay"

osSemaphoreId mySemHandle;

void main() 
{
    osSemaphoreDef(mySem);
    mySemHandle = osSemaphoreCreate(osSemaphore(mySem), 1);
    osSemaphoreRelease(mySemHandle);
}

void LEDGreenTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    /* Accessing to the shared resource */
    osSemaphoreWait(mySemHandle, 16000);
    HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET); 
    delay_16Hz(PIN_BLUE, 32); 
    HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_RESET);
    osSemaphoreRelease(mySemHandle);

    /* Leaving the shared resource */
    delay_16Hz(PIN_GREEN, 64);
    vTaskSuspend(NULL);
  }
}

void LEDRedTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    /* Accessing to the shared resource */
    osSemaphoreWait(mySemHandle, 16000);
    HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET); 
    delay_16Hz(PIN_BLUE, 32); 
    HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_RESET);
    osSemaphoreRelease(mySemHandle);
    
    /* Leaving the shared resource */
    delay_16Hz(PIN_RED, 64);
    vTaskSuspend(NULL);
  }
}

void LEDOrangeTask(void const * argument) 
{
  for(;;) {
    delay_16Hz(PIN_ORANGE, 64);
    vTaskSuspend(NULL);
  }
}