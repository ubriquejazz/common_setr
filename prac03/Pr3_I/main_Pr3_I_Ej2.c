

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

	TickType_t RegTiempo;
	TickType_t Retardo = 1000;
	RegTiempo = xTaskGetTickCount();

  for(;;)
  	{
	  	taskENTER_CRITICAL();
		  if (Flag==1){
        Flag = 0;
        for(long i=0;i<12;i++)
        {
          HAL_GPIO_TogglePin(GPIOD, PIN_GREEN);
          for(long j=0;j<52765;j++)
            __NOP();
        }
        HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_RESET);
        Flag = 1;
		  } 
      else {
        HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET);
      }
      taskEXIT_CRITICAL();

		  vTaskDelayUntil(&RegTiempo, Retardo);
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

	TickType_t RegTiempo;
	TickType_t Retardo = 700;
	RegTiempo = xTaskGetTickCount();

	  for(;;)
	  	{
		  taskENTER_CRITICAL();
			if (Flag==1){
			  Flag = 0;
			  for(long i=0;i<12;i++)
				{
					HAL_GPIO_TogglePin(GPIOD, PIN_RED);
					for(long j=0;j<52765;j++)
						__NOP();
				}
			  HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_RESET);
			  Flag = 1;
			} 
      else {
			  HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET);
			}
			taskEXIT_CRITICAL();
			vTaskDelayUntil(&RegTiempo, Retardo);
	  	}
  /* USER CODE END StartParpLEDRojo */
}
