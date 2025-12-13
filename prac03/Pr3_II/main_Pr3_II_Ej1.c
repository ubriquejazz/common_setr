#include "delay.h"

#define USE_MUTEX 1

osMutexId myMutexHandle;
osSemaphoreId mySemHandle;

void main() {

  // ....

}

void seccion_critica(int pin) {
  HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_SET);
  Blocking_Freq(PIN_BLUE, 2000, LOW_FREQ);
  HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
}

void helper(int pin, int mutex) {
  if (mutex) {
    osMutexWait(myMutexHandle, osWaitForever);
  }
  else {
    osSemaphoreWait(mySemHandle, osWaitForever);
  }
  
  seccion_critica(pin);

  if (mutex)
    osMutexRelease(myMutexHandle);
  else
    osSemaphoreRelease(mySemHandle);
}

/* USER CODE BEGIN Header_StartParpLEDVerde */
/**
  * @brief  Function implementing the ParpLEDVerde thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartParpLEDVerde */
void StartParpLEDVerde(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
  helper(PIN_GREEN, USE_MUTEX);
  Blocking_Freq(PIN_GREEN, 4000, LOW_FREQ);
  vTaskSuspend(NULL);
  }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_StartParpLEDRojo */
/**
* @brief Function implementing the ParpLEDRojo thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartParpLEDRojo */
void StartParpLEDRojo(void const * argument)
{
  /* USER CODE BEGIN StartParpLEDRojo */
  /* Infinite loop */
  osDelay(1000);
  for(;;)
  {
  helper(PIN_RED, USE_MUTEX);
  Blocking_Freq(PIN_RED, 4000, LOW_FREQ);
  vTaskSuspend(NULL);
  }
  /* USER CODE END StartParpLEDRojo */
}

/* USER CODE BEGIN Header_StartParpLEDNaranja */
/**
* @brief Function implementing the ParpLEDNaranja thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartParpLEDNaranja */
void StartParpLEDNaranja(void const * argument)
{
  /* USER CODE BEGIN StartParpLEDNaranja */
  /* Infinite loop */
  osDelay(1000);
  for(;;)
  {
  Blocking_Freq(PIN_ORANGE, 4000, LOW_FREQ);
  vTaskSuspend(NULL);
  }
  /* USER CODE END StartParpLEDNaranja */
}