/* USER CODE BEGIN Header_StartRed */
/**
  * @brief  Function implementing the RedTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartRed */
void StartRed(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */

  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
	  HAL_GPIO_WritePin(GPIOD, PIN_ORANGE, GPIO_PIN_SET);
	  Blocking_20Hz(PIN_RED, 1000); // orange led
	  HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOD, PIN_ORANGE, GPIO_PIN_RESET);
	  vTaskDelayUntil(&lastWakeTime, 2000);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartGreen */
/**
* @brief Function implementing the GreenTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGreen */
void StartGreen(void const * argument)
{
  /* USER CODE BEGIN StartGreen */
  /* Infinite loop */
  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
	  HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET);
	  Blocking_20Hz(PIN_GREEN, 4000);
	  HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET);
	  vTaskDelayUntil(&lastWakeTime, 10000);
  }
  /* USER CODE END StartGreen */
}