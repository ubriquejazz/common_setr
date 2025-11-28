#ifndef DELAY_H
#define DELAY_H

#define PIN_RED         GPIO_PIN_14
#define PIN_ORANGE      GPIO_PIN_13
#define PIN_GREEN       GPIO_PIN_12
#define PIN_BLUE        GPIO_PIN_15

void delay_ms(uint32_t ms);

void Blocking_Flash(uint16_t pin, int duracion_ms);
void Blocking_Freq(uint16_t pin, int duracion_ms, int freq);


#endif // DELAY_H