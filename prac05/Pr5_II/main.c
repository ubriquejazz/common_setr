#include <stdio.h>
#include "../delay.h"
#include "../mailbox.h"

UART_HandleTypeDef huart2;
osMutexId myMutex01Handle;

/* USER CODE BEGIN PV */

Mailbox_t TemperatureMailbox; // Green + Blue
osThreadId GreenTaskHandle;		// TA1
osThreadId BlueTaskHandle;		// TB1

Mailbox_t HumidityMailbox;	// Red + Orange
osThreadId RedTaskHandle;		// TA2
osThreadId OrangeTaskHandle;	// TB2

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
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  Mailbox_Init(&TemperatureMailbox, ID_TEMPERATURA);
  Mailbox_Init(&HumidityMailbox, ID_HUMEDAD);

	/* USER CODE BEGIN RTOS_MUTEX */
  osMutexDef(myMutex01);
  myMutex01Handle = osMutexCreate(osMutex(myMutex01));

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

void StartRed(void const * argument)
{
	Mailbox_t *my_mailbox = (Mailbox_t *)argument;
	int current_humidity = 500; // Humedad inicial (50.0%)
	for(;;)
    {
        current_humidity += 10;
        if (current_humidity > 900)
            current_humidity = 400;

        if (Mailbox_Post(my_mailbox, current_humidity) == pdFALSE)
      	  fatal_error("[H] Posting %d", current_humidity);
        else {
        	  NonBlocking_Flash(PIN_RED, 7000);
        	  osDelay(1000);
        }
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
    	  fatal_error("[T] Posting %d", temp_sensor);
      else {
    	  NonBlocking_Flash(PIN_GREEN, 15000);
    	  osDelay(1000);
      }
	}
}
void StartOrange(void const * argument)
{
	Mailbox_t *shared_mbox = (Mailbox_t *)argument;
	int value1, value2;
	for(;;)
	{
		Mailbox_Pend(shared_mbox);
		value1 = shared_mbox->data;

		osMutexWait(myMutex01Handle, 1000);
		printf("[H] %d %%\r\n", value1);
		osMutexRelease(myMutex01Handle);
	}
}

void StartBlue(void const * argument)
{
	Mailbox_t *shared_mbox = (Mailbox_t *)argument;
	int value1, value2;
	for(;;)
	{
		Mailbox_Pend(shared_mbox);
		value1 = shared_mbox->data;

		osMutexWait(myMutex01Handle, 1000);
		printf("[T] %d oC\r\n", value1);
		osMutexRelease(myMutex01Handle);
	}
}