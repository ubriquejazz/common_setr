#include "../delay.h"
#include "../mailbox.h"

#include <stdio.h>		// for sprintf
#include <string.h>		// for strlen

UART_HandleTypeDef huart2;

Mailbox_t TemperatureMailbox; // Green + Blue
osThreadId GreenTaskHandle;		// TA1
osThreadId BlueTaskHandle;		// TB1

int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(&huart2,(uint8_t *)ptr,len,10);
	return len;
}

void fatal_error(const char* string) {
	printf("[Error] %s", string);
	HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET);
	vTaskSuspend(NULL);
}

void main(void)
{
	// ...
	Mailbox_Init(&TemperatureMailbox, 0);
    
	/* definition and creation of GreenTask */
	osThreadDef(GreenTask, StartGreen, osPriorityNormal, 0, 128);
	GreenTaskHandle = osThreadCreate(osThread(GreenTask), &TemperatureMailbox);

	/* definition and creation of BlueTask */
	osThreadDef(BlueTask, StartBlue, osPriorityNormal, 0, 128);
	BlueTaskHandle = osThreadCreate(osThread(BlueTask), &TemperatureMailbox);

}

void StartGreen(void const * argument)
{
	Mailbox_t *my_mailbox = (Mailbox_t *)argument;
	int temp_sensor = 250; // Dato a enviar
	for(;;)
	{
      temp_sensor += 1;
      if (Mailbox_Post(my_mailbox, temp_sensor) == pdFALSE)
    	  fatal_error("Posting temperature");
      else
    	  NonBlocking_20Hz(PIN_GREEN, 11000); // temperature each 11s
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
		print("Temperatura: %d.%d", received_data / 10, received_data % 10);
	}
}