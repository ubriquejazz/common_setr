#include "delay.h"

osSemaphoreId mySemHandle;

int Flag = 1;

void helper(int pin) {
  osSemaphoreWait(mySemHandle, osWaitForever);
  if (Flag==1){
  Flag = 0;
  } else {
  HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_SET);
  }
  //delay_1s();
  delay_ms(50);
  HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
  Flag = 1;
  osSemaphoreRelease(mySemHandle);
}

void helper_ia(int pin) {
    int action_needed = 0; 

    // Acquire Mutex, protect Flag access, then IMMEDIATELY release.
    osSemaphoreWait(mySemHandle, osWaitForever);
    if (Flag == 1) {
        Flag = 0;
    } else {
        action_needed = 1; // Signal that a blink is needed
    }
    osSemaphoreRelease(mySemHandle);

    // Perform long-duration action OUTSIDE the Mutex protection.
    if (action_needed == 1) {
        HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_SET);
        delay_1s(); // Safely blocking/yielding here, Mutex is free
        HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
        
        // Re-acquire Mutex to safely write to Flag a second time.
        osSemaphoreWait(mySemHandle, osWaitForever);
        Flag = 1; // Complete the state change
        osSemaphoreRelease(mySemHandle);
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
		HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
    helper(PIN_BLUE);
		osDelay(200);
		HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_RESET);
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
  HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);
  helper(PIN_BLUE);
  osDelay(550);
  HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_RESET);
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
