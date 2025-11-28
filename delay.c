#include "main.h"

void delay_ms(uint32_t ms) {
  uint32_t us = ms * 100; // Convert ms to us
  uint32_t count = (SystemCoreClock / 1000000) * us; // Convert us to cycles
  while (count--) {
    __asm__("nop"); // No operation, just wait
  }
}

void delay_1s() {
  // 52765 * 12 = 633180
  for(long i=0;i<12;i++) {
  for(long j=0;j<52765;j++) 
  __NOP();
  }
}
void Blocking_Flash(uint16_t pin, int duracion_ms) {
  int iterations = duracion_ms / 50;
  for (int j=0; j<iterations; j++) {
		HAL_GPIO_TogglePin(GPIOD, pin);
		delay_ms(25);			// 20 Hz = 50 ms
  }
  HAL_GPIO_WritePin(GPIOD, pin , GPIO_PIN_RESET);
}

void Blocking_Freq(uint16_t pin, int duracion_ms, int freq) {
  int iterations = duracion_ms / freq;
  for (int j=0; j<iterations; j++) {
		HAL_GPIO_TogglePin(GPIOD, pin);
		delay_ms(freq/2);			// 20 Hz = 50 ms
  }
}