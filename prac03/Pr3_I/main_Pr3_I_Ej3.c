
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

void Start() {

  int miDelay = 550;
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_XXX, GPIO_PIN_SET);
    helper_ex02(PIN_BLUE);
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
