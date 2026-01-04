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
	  HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);
	  Blocking_Flash(PIN_ORANGE, 1000); // orange led
	  vTaskDelayUntil(&lastWakeTime, 1500);
	  HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_RESET);
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
	  HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
	  Blocking_Flash(PIN_BLUE, 1000); // blue led
	  vTaskDelayUntil(&lastWakeTime, 1500);
	  HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_RESET);
	  vTaskDelayUntil(&lastWakeTime, 2000);
  }
  /* USER CODE END StartGreen */
}
