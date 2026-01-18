#include "delay.h"

int Flag = 1;

void helper(int pin) {
  taskENTER_CRITICAL();
  if (Flag==1){
    Flag = 0;
  } 
  else {
    HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_SET);
  }
  delay_1s(); // blocking delay
  HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
  Flag = 1;
  taskEXIT_CRITICAL();
}

void helper_ia(int pin) {
    // Local variable to store the action state determined by the Flag
    int action_needed = 0; 

    // 1. Safely read and modify the shared resource (Flag)
    taskENTER_CRITICAL();
    if (Flag == 1) {
      Flag = 0;
    } 
    else {
      action_needed = 1; 
    }
    taskEXIT_CRITICAL();

    // 2. Perform long-duration hardware/delay actions *outside* the critical section
    if (action_needed == 1) {
        HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_SET);
        
        // IMPORTANT: Use an RTOS-friendly delay function here, e.g., vTaskDelay()
        // If vTaskDelay is used, the task will yield, allowing other tasks to run.
        delay_1s(); 
        
        HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
        
        // 3. Safely update the Flag after the full action is complete
        taskENTER_CRITICAL();
        Flag = 1; // Set Flag back to 1
        taskEXIT_CRITICAL();
    }
}

void main(void)
{
	// ...
	
	/* definition and creation of RedTask */
	osThreadDef(RedTask, StartRed, osPriorityNormal, 0, 128);
	RedTaskHandle = osThreadCreate(osThread(RedTask), 200);

	/* definition and creation of GreenTask */
	osThreadDef(GreenTask, StartGreen, osPriorityNormal, 0, 128);
	GreenTaskHandle = osThreadCreate(osThread(GreenTask), 550);

	/* definition and creation of OrangeTask */
	osThreadDef(OrangeTask, StartOrange, osPriorityAboveNormal, 0, 128);
	OrangeTaskHandle = osThreadCreate(osThread(OrangeTask), NULL);
	
	// ...

}

void StartRed(void const * argument) {
  int miDelay = 200;
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);
    helper(PIN_BLUE);
    osDelay(miDelay);
    HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_RESET);
    osDelay(miDelay);
  }
  /* USER CODE END 5 */ 
}

void StartGreen(void const * argument) {
  int miDelay = 550;
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
    helper(PIN_BLUE);
    osDelay(miDelay);
    HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_RESET);
    osDelay(miDelay);
  }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_StartParpLEDNaranja */
void StartOrange(void const * argument)
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
