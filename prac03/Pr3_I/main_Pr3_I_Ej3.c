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
  // delay_ms(50); // shorter blocking delay
  
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
        // State 1: Just toggle Flag to 0, no output action needed yet
        Flag = 0;
        // action_needed remains 0
    } 
    else {
        // State 0: Toggle output and set Flag back to 1 later
        action_needed = 1; 
    }
    taskEXIT_CRITICAL();

    // 2. Perform long-duration hardware/delay actions *outside* the critical section
    if (action_needed == 1) {
        // Execute the SET, delay, RESET sequence
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

void Start() {

  int miDelay = 550;
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_XXX, GPIO_PIN_SET);
    helper(PIN_BLUE);
    osDelay(miDelay);
    HAL_GPIO_WritePin(GPIOD, PIN_XXX, GPIO_PIN_RESET);
    osDelay(miDelay);
  }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_StartParpLEDNaranja */
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
