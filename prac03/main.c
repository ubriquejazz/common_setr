

/* USER CODE BEGIN Header_StartParpLedGreen */

int Flag = 1;
mySemaphoreHandle;	// exercise 4
myMutexHandle;		// exercise 5

void helper_ex03() {

	if (Flag) {
		Flag = 0;
		HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET); // blue
		delay_ms(999); // shared resource
		HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET); // blue
		Flag = 1;
	}
}

void helper_ex02() {
	taskENTER_CRITICAL();
	HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET); // blue
	delay_ms(1000);
	HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET); // blue
	taskEXIT_CRITICAL();
}

// mySemaphores could be release somewhere else
void helper_ex04() {
	osSemaphoreWait(mySemaphoreHandle, osWaitForever);
	HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET); // blue
	delay_ms(1000);
	HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET); // blue
	osSemaphoreRelease(mySemaphoreHandle);
}

// myMutex should be released in the same function
void helper_ex05() {
	osMutexWait(myMutexHandle, 1000999);
	HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET); // blue
	delay_ms(1000);
	HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET); // blue
	osMutexRelease(myMutexHandle);
}

/* USER CODE END Header_StartParpLedGreen */
void StartParpLedGreen(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  int DelayTimeMsec=200;
  for(;;)
  {
	  HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
	  helper_ex05();
	  osDelay(DelayTimeMsec);
	  HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_RESET);
	  osDelay(DelayTimeMsec);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartParpLedRojo */
/**
* @brief Function implementing the ParpLedRojo thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartParpLedRojo */
void StartParpLedRojo(void const * argument)
{
  /* USER CODE BEGIN StartParpLedRojo */
  /* Infinite loop */
  int DelayTimeMsec = 550;
  for(;;)
  {
	  HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET); 
	  helper_ex05();
	  osDelay(DelayTimeMsec);
	  HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_RESET);
	  osDelay(DelayTimeMsec);
  }
  /* USER CODE END StartParpLedRojo */
}

/* USER CODE BEGIN Header_StartParpOrange */
/**
* @brief Function implementing the ParpLedOrange thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartParpOrange */
void StartParpOrange(void const * argument)
{
  /* USER CODE BEGIN StartParpOrange */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOD, PIN_ORANGE);
	  osDelay(50);
  }
  /* USER CODE END StartParpOrange */
}
