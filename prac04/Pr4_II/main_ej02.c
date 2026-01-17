#include "delay.h"
#include "cmsis_os.h"

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId BlueTaskHandle;

SemaphoreHandle_t Sync1, Sync2;

void main() {

  MX_GPIO_Init();

  Sync1 = xSemaphoreCreateBinary();
  Sync2 = xSemaphoreCreateBinary();

}

void StartGreen(void const * argument)
{
  for(;;)
  {
    NonBlocking_Freq(PIN_GREEN, 5000, HIG_FREQ);

    // SYNC1: request
    osSemaphoreWait(Sync1, portMAX_DELAY);

    NonBlocking_Freq(PIN_GREEN, 10000, LOW_FREQ);

    // SYNC2: ack
    osSemaphoreRelease(Sync2);
    vTaskSuspend(NULL);
  }
}

void StartRed(void const * argument)
{
  for(;;)
  {
    NonBlocking_Freq(PIN_RED, 10000, LOW_FREQ);

    // SYNC1: ack
    osSemaphoreRelease(Sync1);
    NonBlocking_Freq(PIN_RED, 5000, HIG_FREQ);

    // SYNC2: request
    osSemaphoreWait(Sync2, portMAX_DELAY);
    vTaskSuspend(NULL);
  }
}
