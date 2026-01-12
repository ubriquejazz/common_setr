#include "../delay.h"

#include <stdio.h>		// for sprintf
#include <string.h>		// for strlen

UART_HandleTypeDef huart2;

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId OrangeTaskHandle;
osThreadId BlueTaskHandle;

osThreadId producerID, consumerID;

char uart_msg[50];

void print_uart_msg() {
	HAL_UART_Transmit(&huart2, (uint8_t *)uart_msg, strlen(uart_msg), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
}

void fatal_error() {
	HAL_GPIO_WritePin(GPIOD, PIN_BLUE, GPIO_PIN_SET);
	vTaskSuspend(NULL);
}

const int numChars = 24;
struct CmdData {
  char Cmd[numChars];
  char Obj[numChars];
};
struct CmdData mailbox;

osMutexId valueMutex;
osMutexDef(valueMutex);

void main(void)
{
	// ...
	
	/* definition and creation of RedTask */
	osThreadDef(RedTask, StartRed, osPriorityNormal, 0, 128);
	RedTaskHandle = osThreadCreate(osThread(RedTask), NULL);

	/* definition and creation of GreenTask */
	osThreadDef(GreenTask, StartGreen, osPriorityNormal, 0, 128);
	GreenTaskHandle = osThreadCreate(osThread(GreenTask), NULL);

	/* definition and creation of OrangeTask */
	osThreadDef(OrangeTask, StartOrange, osPriorityNormal, 0, 128);
	OrangeTaskHandle = osThreadCreate(osThread(OrangeTask), NULL);

	/* definition and creation of BlueTask */
	osThreadDef(BlueTask, StartBlue, osPriorityNormal, 0, 128);
	BlueTaskHandle = osThreadCreate(osThread(BlueTask), NULL);

	valueMutex = osMutexCreate(osMutex(valueMutex));

	// Crear Tareas (Threads)
	osThreadDef(Producer, vProducerTask, osPriorityNormal, 0, 128);
	producerID = osThreadCreate(osThread(Producer), NULL);

	osThreadDef(Consumer, vConsumerTask, osPriorityNormal, 0, 128);
	consumerID = osThreadCreate(osThread(Consumer), NULL);

	// --- DISPARADOR INICIAL ---
	// Le decimos al productor que el buffer está "vacío" por primera vez
	osSignalSend(producerID, SIGNAL_READY);
	
	// ...

}

void StartRed(void const * argument) {
	int current_humidity = 500; // Humedad inicial (50.0%)
	for(;;)
    {
		
    }
}

void StartGreen(void const * argument) {
	int temp_sensor = 250; // Dato a enviar
	for(;;)
	{

	}
}

void StartOrange(void const * argument) {
	int received_data;
	for(;;)
	{


		sprintf(uart_msg, "Humedad: %d.%d", 
		received_data / 10, received_data % 10); 
		print_uart_msg();

	}
}

void StartBlue(void const * argument) {
	int received_data;
	for(;;)
	{


		sprintf(uart_msg,"Temperatura: %d.%d", 
		received_data / 10, received_data % 10);
		print_uart_msg();
	}
}

void vProducerTask(void const *argument) {
  for (;;) {
    // Esperar señal de que el buffer está vacío (enviada por el consumidor)
    osSignalWait(0x01, osWaitForever);

    if (1) {
      // Proteger el acceso al mailbox
      osMutexWait(valueMutex, osWaitForever);
      strcpy(mailbox.Cmd, "START");
      strcpy(mailbox.Obj, "ENGINE_01");
      osMutexRelease(valueMutex);

      // Notificar al consumidor que hay datos listos
      osSignalSend(consumerID, 0x01);
    }
  }
}

void vConsumerTask(void const *argument) {
  struct CmdData localCopy;

  for (;;) {
    // Esperar señal de que hay datos disponibles (enviada por el productor)
    osSignalWait(0x01, osWaitForever);

    if (1) {
      // Proteger el acceso para copiar los datos
      osMutexWait(valueMutex, osWaitForever);

	  memcpy(&localCopy, &mailbox, sizeof(struct CmdData));
      osMutexRelease(valueMutex);

      // Procesar comando "localCopy"
	
	  // Notificar al productor que el buffer quedó vacío
      osSignalSend(producerID, 0x01);

    }
  }
}
