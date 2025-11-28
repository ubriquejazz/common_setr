typedef enum { Set, Reset} FlagStatus;

void StartRed(void const * argument)
{
  /* USER CODE BEGIN StartRed */
  /* Infinite loop */ 
  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
	HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);

    // Parpadeo del LED a 10 Hz durante 10s
	Blocking_Flash(PIN_RED, 15000);

    // Set de la bandera a 1

    // Parpadeo del LED a 10 Hz durante 10s
	Blocking_Flash(PIN_RED, 10000);

    // Clear de la bandera a 1

    // Parpadeo del LED a 10 Hz durante 10s
	Blocking_Flash(PIN_RED, 5000);

    // Fin de la tarea

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

    // Parpadeo del LED a 10 Hz durante 10s
	Blocking_Flash(PIN_GREEN, 10000);

    // Set de la bandera a 1

    // Parpadeo del LED a 10 Hz durante 10s

    // Clear de la bandera a 1

    // Parpadeo del LED a 10 Hz durante 10s

    // Fin de la tarea

  }
}

void StartBlue(void const * argument)
{
  /* USER CODE BEGIN StartRed */
  /* Infinite loop */ 
  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
	HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET);

    // Parpadeo del LED a 1 Hz si las dos banderas están en SET

    // Parpadeo del LED a 10 Hz si las dos banderas están en RESET

  }
}