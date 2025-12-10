#include "delay.h"
#include "cmsis_os.h"

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId BlueTaskHandle;

SemaphoreHandle_t Azul2Verde, Azul2Rojo;

void main() {

  MX_GPIO_Init();

  Azul2Verde = xSemaphoreCreateBinary();
  Azul2Rojo = xSemaphoreCreateBinary();

}

void StartRed(void const * argument)
{
  for(;;)
  {
    osSemaphoreWait(Azul2Rojo, portMAX_DELAY);
    NonBlocking_Freq(PIN_RED, 5000, FLASH_HIGH_FREQ);
  }
}

void StartGreen(void const * argument)
{
  for(;;)
  {
    osSemaphoreWait(Azul2Verde, portMAX_DELAY);
    NonBlocking_Freq(PIN_GREEN, 5000, FLASH_HIGH_FREQ);
  }
}

void StartBlue(void const * argument)
{
  for(;;)
  {
    // Parpadeo de 1Hz durante 10s
    NonBlocking_Freq(PIN_BLUE, 10000, FLASH_LOW_FREQ);
    HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_RESET);

    // Set del semaforo
    osSemaphoreRelease(Azul2Verde);
    HAL_Delay(6000);

    // Set del semaforo
    osSemaphoreRelease(Azul2Rojo);
    HAL_Delay(6000);
  }
}