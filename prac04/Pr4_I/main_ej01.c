#include "delay.h"
#include "cflag.h"

CFlag_T Flag1, Flag2;

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId BlueTaskHandle;

void main() {

  MX_GPIO_Init();
  
  /* USER CODE BEGIN 2 */
  if (CFlag_Init(&Flag1) != pdTRUE) {
    // Handle error: could not create the semaphore
    return; 
  }
  if (CFlag_Init(&Flag2) != pdTRUE) {
    // Handle error: could not create the semaphore
    return; 
  }
  /* USER CODE END 2 */

}

void StartRed(void const * argument)
{
  for(;;)
  {
    // Parpadeo del LED a HF
    Blocking_Freq(PIN_RED, 15000, FLASH_HIGH_FREQ);

    // Set de la bandera a 1
    CFlag_Set(&Flag1);

    // Parpadeo del LED a LF
    Blocking_Freq(PIN_RED, 10000, FLASH_LOW_FREQ);

    // Clear de la bandera a 1
    CFlag_Clear(&Flag1);

    // Parpadeo del LED a HF
    Blocking_Freq(PIN_RED, 5000, FLASH_HIGH_FREQ);

    vTaskSuspend(NULL);
  }
}

void StartGreen(void const * argument)
{

  for(;;)
  {
    // Parpadeo del LED a HF
    Blocking_Freq(PIN_GREEN, 10000, FLASH_HIGH_FREQ);
    
    // Set de la bandera a 2
    CFlag_Set(&Flag2);

    // Parpadeo del LED a LF
    Blocking_Freq(PIN_GREEN, 10000, FLASH_LOW_FREQ);

    // Clear de la bandera a 2
    CFlag_Clear(&Flag2);

    // Parpadeo del LED a HF
    Blocking_Freq(PIN_GREEN, 10000, FLASH_HIGH_FREQ);

    vTaskSuspend(NULL);
  }
  
}

void StartBlue(void const * argument)
{
  int delay = 1000;
  for(;;)
  {
    // Parpadeo del LED a LF inicial
    Blocking_Freq(PIN_BLUE, delay, FLASH_HIGH_FREQ);

    // Parpadeo del LED a HF o LF según el estado de las banderas
    if ((Flag1.state == Set) && (Flag2.state == Set))
      Blocking_Freq(PIN_BLUE, delay, FLASH_LOW_FREQ);
    else if ((Flag1.state == Reset) && (Flag2.state == Reset))
      Blocking_Freq(PIN_BLUE, delay, FLASH_HIGH_FREQ);
    else {
      HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET);
      osDelay(delay);
    }
  }
}