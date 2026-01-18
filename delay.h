#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

#define PIN_RED         GPIO_PIN_14
#define PIN_ORANGE      GPIO_PIN_13
#define PIN_GREEN       GPIO_PIN_12
#define PIN_BLUE        GPIO_PIN_15

#define HIG_FREQ		  60
#define LOW_FREQ		  180
#define MAX_ITERATE		105530 // 16Hz

void delay_ms(uint32_t ms);
void Blocking_20Hz(uint16_t pin, int duracion_ms);
void Blocking_Freq(uint16_t pin, int duracion_ms, int period);

void NonBlocking_20Hz(uint16_t pin, int duracion_ms);
void NonBlocking_Freq(uint16_t pin, int duracion_ms, int period);

void delay_16Hz(uint16_t pin, int times);
void delay_125ms();
void delay_1s();
void delay_2s();

#endif // DELAY_H
