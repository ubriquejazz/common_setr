#include <stdio.h>

/* Private variables -----------------------------------------*/ 
osThreadId Task1Handle;
osThreadId Task2Handle;
osMutexId myMutex01Handle;

UART_HandleTypeDef huart2;

int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(&huart2,(uint8_t *)ptr,len,10);
	return len;
}

void main() {

    /* definition and creation of myMutex01 */
    osMutexDef(myMutex01);
    myMutex01Handle = osMutexCreate(osMutex(myMutex01));

}

void StartTask1(void const * argument) 
{
    /* USER CODE BEGIN StartTask1 */ 
    /* Infinite loop */
    for(;;)
    {
    osDelay(2000);
    osMutexWait(myMutex01Handle,1000);
    printf("Task1 Print\n");
    osMutexRelease(myMutex01Handle); 
    }
    /* USER CODE END 5 */
}

void StartTask2(void const * argument) 
{
    /* USER CODE BEGIN StartTask2 */ 
    /* Infinite loop */
    for(;;)
    {
    osDelay(2000);
    osMutexWait(myMutex01Handle,1000);
    printf("Task2 Print\n");
    osMutexRelease(myMutex01Handle); 
    }
    /* USER CODE END 5 */
}