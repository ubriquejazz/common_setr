
int Flag = 1;

void helper_ex02(int pin) {

  taskENTER_CRITICAL();
  if (Flag==1){
    Flag = 0;
  } 
  else {
    HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_SET);
  }
		
  for(long i=0;i<12;i++) {
    for(long j=0;j<52765;j++) {
      __NOP();
    }
  }
	HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
  Flag = 1;
  taskEXIT_CRITICAL();
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
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
    helper_ex02(PIN_BLUE);
		osDelay(200);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
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
void StartParpLEDRojo(void const * argument)
{
  /* USER CODE BEGIN StartParpLEDRojo */
  /* Infinite loop */

	  for(;;)
	  	{
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
      helper_ex02(PIN_BLUE);  
			osDelay(550);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
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
void StartParpLEDNaranja(void const * argument)
{
  /* USER CODE BEGIN StartParpLEDNaranja */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(GPIOD, PIN_ORANGE);
	  osDelay(50);
  }
  /* USER CODE END StartParpLEDNaranja */
}
