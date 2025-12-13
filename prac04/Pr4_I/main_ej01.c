#include "../delay.h"
#include "../cflag.h"

osThreadId RedTaskHandle;
osThreadId GreenTaskHandle;
osThreadId BlueTaskHandle;

CFlag_t Flag1, Flag2;
char huart2_msg[50];

void print_msg() {
	HAL_UART_Transmit(&huart2, (uint8_t *)huart2_msg, strlen(huart2_msg), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
}

void CFlag_Test() {
	if (CFlag_Init(&Flag1) == pdTRUE)
	if (CFlag_Set(&Flag1) == pdTRUE)
		sprintf(huart2_msg, "Flag1 value: %d", Flag1.data);
	else
		sprintf(huart2_msg, "Flag1: Cant write!");
	else
	  sprintf(huart2_msg, "Flag1: No initialized!");
	print_msg();

	if (CFlag_Init(&Flag2) == pdTRUE)
	if (CFlag_Set(&Flag2) == pdTRUE)
		sprintf(huart2_msg, "Flag2 value: %d", Flag2.data);
	else
		sprintf(huart2_msg, "Flag2: Cant write!");
	else
	  sprintf(huart2_msg, "Flag2: No initialized!");
	print_msg();
}

void main() {

  MX_GPIO_Init();
  Cflag_Test();

}

void StartRed(void const * argument)
{
  for(;;)
  {
    // Parpadeo del LED a HF
    Blocking_Freq(PIN_RED, 10000, HIG_FREQ);

    // Set de la bandera a 1
    CFlag_Set(&Flag1);

    // Parpadeo del LED a LF
    Blocking_Freq(PIN_RED, 15000, LOW_FREQ);

    // Clear de la bandera a 1
    CFlag_Clear(&Flag1);

    // Parpadeo del LED a HF
    Blocking_Freq(PIN_RED, 5000, HIG_FREQ);

    vTaskSuspend(NULL);
  }
}

void StartGreen(void const * argument)
{

  for(;;)
  {
    // Parpadeo del LED a HF
    Blocking_Freq(PIN_GREEN, 10000, HIG_FREQ);
    
    // Set de la bandera a 2
    CFlag_Set(&Flag2);

    // Parpadeo del LED a LF
    Blocking_Freq(PIN_GREEN, 10000, LOW_FREQ);

    // Clear de la bandera a 2
    CFlag_Clear(&Flag2);

    // Parpadeo del LED a HF
    Blocking_Freq(PIN_GREEN, 10000, HIG_FREQ);

    vTaskSuspend(NULL);
  }
  
}

void StartBlue(void const * argument)
{
  int delay = 100;
  CFlagState_t aux1, aux2;

  for(;;)
  {
		// Parpadeo del LED según el estado de las banderas
    // 10 Hz es HF, 1 Hz es LF

    aux1 = Flag1.state; // CFlag_Wait(&Flag1);
    aux2 = Flag2.state; // CFlag_Wait(&Flag2);

		if ((aux1 == Set) && (aux2 == Set)) {
			HAL_GPIO_WritePin(GPIOD, PIN_BLUE , GPIO_PIN_SET);
	    	//NonBlocking_Freq(PIN_BLUE, delay, LOW_FREQ);
		}
		else if ((aux1 == Reset) && (aux2 == Reset)) {
			HAL_GPIO_WritePin(GPIOD, PIN_BLUE , GPIO_PIN_RESET);
			//NonBlocking_Freq(PIN_BLUE, delay, HIG_FREQ);
		}
		else {
		    NonBlocking_Freq(PIN_BLUE, delay, HIG_FREQ);
		  }
	  }
}