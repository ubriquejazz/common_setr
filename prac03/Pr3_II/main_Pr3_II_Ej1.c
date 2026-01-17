#include "delay.h"

#define USE_MUTEX 1

osMutexId myMutexHandle;
osSemaphoreId mySemHandle;

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
	
	// Create semaphore or mutex and release it to start
  if (mutex) {
    osMutexDef(myMutex);
    myMutexHandle = osMutexCreate(osMutex(myMutex));
    osMutexRelease(myMutexHandle);
  }
  else {
    osSemaphoreDef(mySem);
    mySemHandle = osSemaphoreCreate(osSemaphore(mySem), 1);
    osSemaphoreRelease(mySemHandle);
  }

  // ...
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

void StartGreen(void const * argument)
{
  /* Infinite loop */
  for(;;)
  {
  helper(PIN_GREEN, USE_MUTEX);
  Blocking_Freq(PIN_GREEN, 4000, LOW_FREQ);
  vTaskSuspend(NULL);
  }
  /* USER CODE END 5 */ 
}

void StartRed(void const * argument)
{
  /* Infinite loop */
  osDelay(1000);
  for(;;)
  {
  helper(PIN_RED, USE_MUTEX);
  Blocking_Freq(PIN_RED, 4000, LOW_FREQ);
  vTaskSuspend(NULL);
  }
  /* USER CODE END */
}

void StartOrange(void const * argument)
{
  /* Infinite loop */
  osDelay(1000);
  for(;;)
  {
  Blocking_Freq(PIN_ORANGE, 4000, LOW_FREQ);
  vTaskSuspend(NULL);
  }
  /* USER CODE END */
}