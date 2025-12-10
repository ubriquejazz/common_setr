#include "main.h"
#include "delay.h"

void delay_ms(uint32_t ms) {
  uint32_t us = ms * 100; // Convert ms to us
  uint32_t count = (SystemCoreClock / 1000000) * us; // Convert us to cycles
  while (count--) {
    __asm__("nop"); // No operation, just wait
  }
}

void delay_10Hz(uint16_t pin, int iterations) {
	for(long i=0;i<iterations;i++)
	{
		if (pin) HAL_GPIO_TogglePin(GPIOD, pin);
		for(long j=0;j<52765;j++)
		{
			__NOP();
		}
	}
	if (pin) HAL_GPIO_WritePin(GPIOD, pin, GPIO_PIN_RESET);
}

void Blocking_Flash(uint16_t pin, int duracion_ms) {
  int iterations = duracion_ms / 50;
  for (int j=0; j<iterations; j++) {
		HAL_GPIO_TogglePin(GPIOD, pin);
		delay_ms(25);			// 20 Hz = 50 ms
  }
  HAL_GPIO_WritePin(GPIOD, pin , GPIO_PIN_RESET);
}

void Blocking_Freq(uint16_t pin, int duracion_ms, int period) {
  int iterations = duracion_ms / period;
  for (int j=0; j<iterations; j++) {
		HAL_GPIO_TogglePin(GPIOD, pin);
		delay_ms(period/2);
  }
  HAL_GPIO_WritePin(GPIOD, pin , GPIO_PIN_RESET);
}

/*****************/

void NonBlocking_Flash(uint16_t pin, int duracion_ms) {
  int iterations = duracion_ms / 50;
  for (int j=0; j<iterations; j++) {
		HAL_GPIO_TogglePin(GPIOD, pin);
		osDelay(25);			// 20 Hz = 50 ms
  }
  HAL_GPIO_WritePin(GPIOD, pin , GPIO_PIN_RESET);
}

void NonBlocking_Freq(uint16_t pin, int duracion_ms, int period) {
  int iterations = duracion_ms / period;
  for (int j=0; j<iterations; j++) {
		HAL_GPIO_TogglePin(GPIOD, pin);
		osDelay(period/2);
  }
  HAL_GPIO_WritePin(GPIOD, pin , GPIO_PIN_RESET);
}

/*****************/


void delay_1s() {
	delay_10Hz(0, 12); // 52765 * 12 = 633180
}

