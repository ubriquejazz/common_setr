#include "../delay.h"
#include "../mailbox.h"

#include <stdio.h>		// for sprintf
#include <string.h>		// for strlen

UART_HandleTypeDef huart2;

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId OrangeTaskHandle;
osThreadId BlueTaskHandle;

Mailbox_t HumidityMailbox;	// Red + Orange
Mailbox_t TemperatureMailbox; // Green + Blue

char uart_msg[50];

void print_uart_msg() {
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_msg, strlen(uart_msg), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
}

void fatal_error() {
	HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET);
	vTaskSuspend(NULL);
}

void main_init(void)
{
	// ...
	Mailbox_Init(&TemperatureMailbox, 0);
	Mailbox_Init(&HumidityMailbox, 0);

	/* definition and creation of RedTask */
	osThreadDef(RedTask, StartRed, osPriorityNormal, 0, 128);
	RedTaskHandle = osThreadCreate(osThread(RedTask), &HumidityMailbox);

	/* definition and creation of GreenTask */
	osThreadDef(GreenTask, StartGreen, osPriorityNormal, 0, 128);
	GreenTaskHandle = osThreadCreate(osThread(GreenTask), &TemperatureMailbox);

	/* definition and creation of OrangeTask */
	osThreadDef(OrangeTask, StartOrange, osPriorityNormal, 0, 128);
	OrangeTaskHandle = osThreadCreate(osThread(OrangeTask), &HumidityMailbox);

	/* definition and creation of BlueTask */
	osThreadDef(BlueTask, StartBlue, osPriorityNormal, 0, 128);
	BlueTaskHandle = osThreadCreate(osThread(BlueTask), &TemperatureMailbox);

}

void StartRed(void const * argument) {
{
	Mailbox_t *my_mailbox = (Mailbox_t *)argument;
	int current_humidity = 500; // Humedad inicial (50.0%)
	for(;;)
    {
        current_humidity += 10;
        if (current_humidity > 900)
        {
            current_humidity = 400;
        }
        if (Mailbox_Post(my_mailbox, current_humidity) == pdFALSE)
      	  fatal_error();
        else
      	  NonBlocking_Flash(PIN_RED, 19000); // humidity each 19s
    }
}

void StartGreen(void const * argument)
{
	Mailbox_t *my_mailbox = (Mailbox_t *)argument;
	int temp_sensor = 250; // Dato a enviar
	for(;;)
	{
      temp_sensor += 1;
      if (Mailbox_Post(my_mailbox, temp_sensor) == pdFALSE)
    	  fatal_error();
      else
    	  NonBlocking_Flash(PIN_GREEN, 11000); // temperature each 11s
	}
}

void StartOrange(void const * argument)
{
	Mailbox_t *shared_mbox = (Mailbox_t *)argument;
	int received_data;
	for(;;)
	{
		Mailbox_Pend(shared_mbox);
		received_data = shared_mbox->data;
		sprintf(uart_msg, "Humedad: %d.%d", 
		received_data / 10, received_data % 10); 
		print_uart_msg();

	}
}

void StartBlue(void const * argument)
{
	Mailbox_t *shared_mbox = (Mailbox_t *)argument;
	int received_data;
	for(;;)
	{
		Mailbox_Pend(shared_mbox);
		received_data = shared_mbox->data;
		sprintf(uart_msg,"Temperatura: %d.%d", 
		received_data / 10, received_data % 10);
		print_uart_msg();
	}
}