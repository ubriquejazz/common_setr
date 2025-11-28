
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
    int action_needed = 0; // Local flag to determine action outside the Mutex

    // 1. Acquire the Mutex to safely access and modify the shared Flag
    osSemaphoreWait(SemaforoRecursoCritico1Handle, osWaitForever);
    
    if (Flag == 1) {
        // State 1: Reset Flag to 0. No immediate output action needed.
        Flag = 0;
        // action_needed remains 0
    } else {
        // State 0: Prepare to perform the output action (blink) and set Flag back to 1 later.
        action_needed = 1;
    }
    
    // 2. RELEASE the Mutex immediately after accessing the shared resource
    osSemaphoreRelease(SemaforoRecursoCritico1Handle);

    // 3. Perform the time-consuming action *outside* of the Mutex protection
    if (action_needed == 1) {
        // Execute the SET, delay, RESET sequence
        HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_SET);
        
        // This delay is now safe, as the Mutex is released, and other tasks
        // can acquire the Mutex and proceed with their critical sections.
        delay_1s(); 
        
        HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
        
        // 4. Re-acquire the Mutex to safely update the Flag after the action is complete
        osSemaphoreWait(SemaforoRecursoCritico1Handle, osWaitForever);
        Flag = 1; // Set Flag back to 1
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
