#include "delay.h"

int Flag = 1;

void helper_ej01(int pin) {

  //taskENTER_CRITICAL();
  if (Flag==1){
    Flag = 0;
    delay_16Hz(pin, 8);
    Flag = 1;
  } 
  else {
    HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET);
  }
  //taskEXIT_CRITICAL();
}

void StartParpLEDVerde(void const * argument)
{
TickType_t RegTiempo;
TickType_t Retardo = 1000;
RegTiempo = xTaskGetTickCount();

for(;;)
{
  helper_ej01(PIN_GREEN);
  vTaskDelayUntil(&RegTiempo, Retardo);
}
/* USER CODE END 5 */ 
}

void StartParpLEDRojo(void const * argument)
{
TickType_t RegTiempo;
TickType_t Retardo = 700;
RegTiempo = xTaskGetTickCount();

for(;;)
{
  helper_ej01(PIN_RED);
  vTaskDelayUntil(&RegTiempo, Retardo);
}
/* USER CODE END StartParpLEDRojo */
}
