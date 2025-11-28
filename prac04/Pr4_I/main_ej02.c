
void StartRed(void const * argument)
{
  /* USER CODE BEGIN StartRed */
  /* Infinite loop */ 
  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);

    // Tarea receptoras
    osSignalWait(0x0001, osWaitForever);

    // Parpadeo del LED a 1 Hz durante 10 s
    Blocking_Flash(PIN_RED, 5000);

  }
}

void StartGreen(void const * argument)
{
  /* USER CODE BEGIN StartGreen */
  /* Infinite loop */
  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
	  HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);

    // Tarea receptoras
    osSignalWait(0x0001, osWaitForever);

    // Parpadeo del LED a 1 Hz durante 10 s
    Blocking_Flash(PIN_GREEN, 10000);
  }
}

void StartBlue(void const * argument)
{
  /* USER CODE BEGIN StartRed */
  /* Infinite loop */ 
  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {

    HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET);

    // Parpadeo del LED a 1 Hz durante 10 s
    Blocking_Flash(PIN_BLUE, 10000);

    // SEND signal to Red and Green tasks
    osSignalSet(StartGreen, 0x0001);
    osDelay(6000);
    osSignalSet(StartRed, 0x0001);
    osDelay(6000);

  }
}