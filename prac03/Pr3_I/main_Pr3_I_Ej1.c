#include "delay.h"

int Flag = 1;

void helper_ej01(int pin) {

  //taskENTER_CRITICAL();
  if (Flag==1){
    Flag = 0;
    for(long i=0;i<8;i++){
      HAL_GPIO_TogglePin(GPIOD, pin);
      for(long j=0;j<65535;j++)
        __NOP();
    }
    HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
    Flag = 1;
  } 
  else {
    HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET);
  }
  //taskEXIT_CRITICAL();
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

/* USER CODE BEGIN Header_StartParpLEDRojo */
/**
* @brief Function implementing the ParpLEDRojo thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartParpLEDRojo */
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
