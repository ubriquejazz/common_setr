#include "../blink.h"

TaskHandle_t taskTally;
TaskHandle_t taskHighwater;

void main() 
{ 
    Serial.begin(115200);

    //...

    xTaskCreate (TaskOLED, "", NULL, 2, &taskTally); 
    xTaskCreate (TaskHighWater, "", NULL, 2, &taskHighwater); 
    //...
}

void TaskOLED(void *pvParameters)  // {
  TickType_t xLastWaitTime;  // define the last update time (in ticks)
  xLastWaitTime = xTaskGetTickCount();
  for(;;){
    // numer of lamps lit from global variables
    int numLit = redLED + greenLED + blueLED;
    //Display.println(String(numLit));
    //...
    // short unblocked delay between readings (1/10 second)
    xTaskDelayUntil(&xLastWaitTime, pdMS_TO_TICKS(100));
  }
}

void TaskHighWater(void *pvParameters) {
  for(;;){
    vTaskDelay(5000);   // wait 5 seconds so system is fully running
    Serial.println("***************************");
    Serial.print("High Water Mark for Green LED : ");
    Serial.println(uxTaskGetStackHighWaterMark(taskGreen));
    Serial.print("High Water Mark for red LED : ");
    Serial.println(uxTaskGetStackHighWaterMark(taskRed));
    Serial.print("High Water Mark for Blue LED : ");
    Serial.println(uxTaskGetStackHighWaterMark(taskBlue));
    Serial.print("High Water Mark for Tally : ");
    Serial.println(uxTaskGetStackHighWaterMark(taskTally));
    Serial.print("High Water Mark for Highwater Task: ");
    Serial.println(uxTaskGetStackHighWaterMark(taskHighwater));
    //Serial.print("High Water Mark for Speedup: ");
    //Serial.println(uxTaskGetStackHighWaterMark(taskSpeedup));
    Serial.flush(); // make sure last data is written
    vTaskSuspend(NULL); // run this task only once
  }
}