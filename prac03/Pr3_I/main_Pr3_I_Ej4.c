#include "../delay.h"

#define USE_MUTEX 1

osMutexId myMutexHandle;
osSemaphoreId mySemHandle;

int Flag = 1;

void seccion_critica(int pin) {
  if (Flag==1){
    Flag = 0;
  } else {
    HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_SET);
  }
  //delay_1s();
  delay_ms(50);
  HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
  Flag = 1;
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
    osMutexRelease(mySemHandle);
  else
  osSemaphoreRelease(mySemHandle);
}

void main(void)
{
	// ...
	
	/* definition and creation of RedTask */
	osThreadDef(RedTask, StartRed, osPriorityNormal, 0, 128);
	RedTaskHandle = osThreadCreate(osThread(RedTask), 200);

	/* definition and creation of GreenTask */
	osThreadDef(GreenTask, StartGreen, osPriorityNormal, 0, 128);
	GreenTaskHandle = osThreadCreate(osThread(GreenTask), 550);

	/* definition and creation of OrangeTask */
	osThreadDef(OrangeTask, StartOrange, osPriorityAboveNormal, 0, 128);
	OrangeTaskHandle = osThreadCreate(osThread(OrangeTask), NULL);
	
	// Create semaphore or mutex

  // Release to start
  if (mutex)
    osMutexRelease(mySemHandle);
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
void StartGreen(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */

  for(;;)
  	{
		HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
    helper(PIN_BLUE, USE_MUTEX);
		osDelay(200);
		HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_RESET);
		osDelay(200);
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
void StartRed(void const * argument)
{
/* USER CODE BEGIN StartParpLEDRojo */
/* Infinite loop */

for(;;)
  {
  HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);
  helper(PIN_BLUE, USE_MUTEX);
  osDelay(550);
  HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_RESET);
  osDelay(550);
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
void StartOrange(void const * argument)
{
/* USER CODE BEGIN StartParpLEDNaranja */
/* Infinite loop */
for(;;)
{
  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
  osDelay(50);
}
/* USER CODE END StartParpLEDNaranja */
}
