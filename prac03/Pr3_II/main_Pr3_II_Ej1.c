

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
    osSemaphoreWait(mySemHandle, osWaitForever);
    HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
    delay_2s_10Hz(PIN_BLUE);
    HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_RESET);
    osSemaphoreRelease(mySemHandle);

    delay_4s_10Hz(PIN_GREEN);
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
osSemaphoreWait(mySemHandle, osWaitForever);
HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);
delay_2s_10Hz(PIN_BLUE);
HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_RESET);
osSemaphoreRelease(mySemHandle);

delay_4s_10Hz(PIN_RED);
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
for(;;)
{
  osDelay(1000);
  delay_4s_10Hz(PIN_ORANGE);
  vTaskSuspend(NULL);
}
  /* USER CODE END StartParpLEDNaranja */
}