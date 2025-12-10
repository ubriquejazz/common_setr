#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

#define PIN_RED         GPIO_PIN_14
#define PIN_ORANGE      GPIO_PIN_13
#define PIN_GREEN       GPIO_PIN_12
#define PIN_BLUE        GPIO_PIN_15

#define FLASH_HIGH_FREQ		60
#define FLASH_LOW_FREQ		180

void delay_ms(uint32_t ms);

void Blocking_Flash(uint16_t pin, int duracion_ms);
void Blocking_Freq(uint16_t pin, int duracion_ms, int);

void NonBlocking_Flash(uint16_t pin, int duracion_ms);
void NonBlocking_Freq(uint16_t pin, int duracion_ms, int);

void delay_1s();

#endif // DELAY_H
