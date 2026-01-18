#include <stdio.h>

/* Private variables ---------------------------------------------------------*/ 
osThreadId Sender1Handle;
osThreadId ReceiverHandle;
osMessageQId Queue1Handle;

UART_HandleTypeDef huart2;

int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(&huart2,(uint8_t *)ptr,len,10);
	return len;
}

/* DATA variables ------------------------------------------------------------*/ 
/* Define the structure type that will be passed on the queue. */ typedef struct
typedef struct {
    uint16_t Value;
    uint8_t Source; 
} Data;

/* Declare two variables of type Data that will be passed on the queue. */
Data DataToSend1={0x2018,1};
Data DataToSend2={0x2019,2};

void main() {
    /* Create the queue(s) definition and creation of Queue1 */
    osMessageQDef(Queue1, 256, uint8_t);
    Queue1Handle = osMessageCreate(osMessageQ(Queue1), NULL);
}

void StartReceiver(void const * argument)
{
    /* USER CODE BEGIN StartReceiver */
    osEvent retvalue;
    /* Infinite loop */
    for(;;) {

        printf("Task2\n");
        retvalue = osMessageGet(Queue1Handle,4000); 

        if(((Data*)retvalue.value.p)->Source==1){
            printf("Receiver Receive message from Sender 1\n");
        }
        else{
            printf("Receiver Receive message from Sender 2\n");
        }
        printf("%d \n",((Data*)retvalue.value.p)->Value); 
    }
    /* USER CODE END StartReceiver */
}

void StartSender1(void const * argument) 
{
    /* USER CODE BEGIN 5 */ 
    /* Infinite loop */ 
    for(;;) {
        printf("Task1\n");
        osMessagePut(Queue1Handle, (uint32_t)&DataToSend1,200);
        osDelay(1000);
    }
    /* USER CODE END 5 */
}