#include <stdio.h>
#define XXX 65535

osSemaphoreId mySemHandle;

inline delay_inline() {
  for(long j=0;j<XXX;j++)
  __NOP();
}
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
    for(long i=0;i<32;i++) {
      HAL_GPIO_TogglePin(GPIOD, PIN_BLUE); 
delay_inline();
    }

    HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_RESET);
    osSemaphoreRelease(XXX);
    /* Leaving the shared resource */
    for(long i=0;i<64;i++) {
      HAL_GPIO_TogglePin(GPIOD, PIN_GREEN); 
delay_inline();
    }
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
    for(long i=0;i<32;i++) {
      HAL_GPIO_TogglePin(GPIOD, PIN_BLUE); 
delay_inline();
    }

    HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_RESET);
    osSemaphoreRelease(XXX);
    /* Leaving the shared resource */
    for(long i=0;i<64;i++) {
      HAL_GPIO_TogglePin(GPIOD, PIN_RED); 
delay_inline();
    }
    vTaskSuspend(NULL);
  }
}

void LEDOrangeTask(void const * argument) 
{
  for(;;) {
    for(long i=0;i<64;i++)
    {
      HAL_GPIO_TogglePin(GPIOD, PIN_ORANGE);
delay_inline();
    }
    vTaskSuspend(NULL);
  }
}