
/* USER CODE BEGIN Header_StartGreen */
/**
  * @brief  Function implementing the GreenTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartGreen */
void StartGreen(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osSemaphoreWait(myBinarySem01Handle, osWaitForever);
    HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
    Blocking_Flash(PIN_BLUE, 2000);
    HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET);
    osSemaphoreRelease(myBinarySem01Handle);
    //
    Blocking_Flash(PIN_GREEN, 4000);
    vTaskSuspend(NULL);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartRed */
/**
* @brief Function implementing the RedTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRed */
void StartRed(void const * argument)
{
  /* USER CODE BEGIN StartRed */
  /* Infinite loop */
  for(;;)
  {
        osDelay(1000);
        osSemaphoreWait(myBinarySem01Handle, osWaitForever);
        HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);
        Blocking_Flash(PIN_BLUE, 2000);
        HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET);
        osSemaphoreRelease(myBinarySem01Handle);
        // 
        Blocking_Flash(PIN_RED, 4000);
        vTaskSuspend(NULL);
  }
  /* USER CODE END StartRed */
}

/* USER CODE BEGIN Header_StartBlue */
/**
* @brief Function implementing the BlueTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBlue */
void StartBlue(void const * argument)
{
  /* USER CODE BEGIN StartBlue */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(1000);
	  Blocking_Flash(PIN_ORANGE, 4000);
	  vTaskSuspend(NULL);
  }
  /* USER CODE END StartBlue */
}
