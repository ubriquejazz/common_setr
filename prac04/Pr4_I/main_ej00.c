#include "../delay.h"
#include "../cflag.h"

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId BlueTaskHandle;

CFlag_t Flag1, Flag2;

void StartRed(void const * argument)
{
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_RED, GPIO_PIN_SET);
	CFlag_Set(&Flag1, 1);
    NonBlocking_Freq(PIN_RED, 5000, HIG_FREQ);
    osDelaya(1000);
  }
}

void StartGreen(void const * argument)
{
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOD, PIN_GREEN, GPIO_PIN_SET);
	CFlag_Set(&Flag2, 1);
    NonBlocking_Freq(PIN_GREEN, 5000, HIG_FREQ);
    osDelaya(1000);
  }
}

void StartBlue(void const * argument)
{
  for(;;)
  {
    int a = CFlag_Get(&Flag1);
    int b = CFlag_Get(&Flag2);

    // si ambas en SET, pasar a parpadea a LF. 
    if (a == 1) && (b == 1)
        NonBlocking_Freq(PIN_BLUE, 5000, LOW_FREQ);

    // si ambas en CLR, pasar a parpadea a HF. 
        if (a == 0) && (b == 0)
        NonBlocking_Freq(PIN_BLUE, 5000, HIG_FREQ);
  }
}
