#include "../delay.h"

#include <stdio.h>		// for sprintf
#include <string.h>		// for strlen

UART_HandleTypeDef huart2;

osThreadId producerID, consumerID;


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
