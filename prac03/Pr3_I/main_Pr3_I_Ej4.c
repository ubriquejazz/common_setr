
osThreadId ParpLEDVerdeHandle;
osThreadId ParpLEDRojoHandle;
osThreadId ParpLEDNaranjaHandle;

osSemaphoreId SemaforoRecursoCritico1Handle;
int Flag = 1;

void helper(int pin) {
  osSemaphoreWait(SemaforoRecursoCritico1Handle, osWaitForever);
  if (Flag==1){
  Flag = 0;
  } else {
  HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_SET);
  }
  delay_1s();
  HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
  Flag = 1;
  osSemaphoreRelease(SemaforoRecursoCritico1Handle);
}

void helper_ia(int pin) {
    int action_needed = 0; 

    // Acquire Mutex, protect Flag access, then IMMEDIATELY release.
    osSemaphoreWait(SemaforoRecursoCritico1Handle, osWaitForever);
    if (Flag == 1) {
        Flag = 0;
    } else {
        action_needed = 1; // Signal that a blink is needed
    }
    osSemaphoreRelease(SemaforoRecursoCritico1Handle);

    // Perform long-duration action OUTSIDE the Mutex protection.
    if (action_needed == 1) {
        HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_SET);
        delay_1s(); // Safely blocking/yielding here, Mutex is free
        HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
        
        // Re-acquire Mutex to safely write to Flag a second time.
        osSemaphoreWait(SemaforoRecursoCritico1Handle, osWaitForever);
        Flag = 1; // Complete the state change
        osSemaphoreRelease(SemaforoRecursoCritico1Handle);
    }
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
    helper(PIN_BLUE);
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
  helper(PIN_BLUE);
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
  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
  osDelay(50);
}
/* USER CODE END StartParpLEDNaranja */
}
