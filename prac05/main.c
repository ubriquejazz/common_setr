#include "mailbox.h"

UART_HandleTypeDef huart2;

void println(const char *msg) {
	HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
}

void StartRed(void const * argument) {
{
int freq=99;
char msg[50];
for(;;)
{
sprintf(msg, "Rojo: %d", freq); println(msg);
osDelay(6000);
}
}
