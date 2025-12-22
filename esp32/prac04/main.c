#include "../blink.h"

UBaseType_t uxTaskGetStackHighWaterMark(TaskHandle_t xTask);

TimerHandle_t   highwaterTimer; // define data types for the highwater mark timer
BaseType_t      hwTimerStarted; 

void TaskHighWater(void *pvParameters)
{
  while (true) {
    // wait 5 seconds so system is fully running
    // display highwater marks for all 6 tasks
    Serial.println("***************************");
    Serial.print("High Water Mark for Green LED : ");
    Serial.println(uxTaskGetStackHighWaterMark(taskGreen));
    Serial.print("High Water Mark for Red LED : ");
    Serial.println(uxTaskGetStackHighWaterMark(taskRed));
    Serial.print("High Water Mark for Blue LED : ");
    Serial.println(uxTaskGetStackHighWaterMark(taskBlue));
    Serial.print("High Water Mark for Tally : ");
    Serial.println(uxTaskGetStackHighWaterMark(taskTally));
    Serial.print("High Water Mark for Highwater Task: ");
    Serial.println(uxTaskGetStackHighWaterMark(taskHighwater));
    Serial.print("High Water Mark for Speed: ");
    Serial.println(uxTaskGetStackHighWaterMark(taskSpeed));
    Serial.flush(); // make sure last data is written
    vTaskSuspend(NULL); // run this task only once
  }
}

void hwCallback( TimerHandle_t xTimer )
{
    vTaskResume(taskHighwater); // run the highwater program once
}

void main() 
{ 
    Serial.begin(115200);

    // setup button for interupt processing
    pinMode(pinButton, INPUT_PULLUP);
    attachInterrupt(pinButton, buttonPush, FALLING);

    highwaterTimer = xTimerCreate("", 10000, pdTRUE, 0, hwCallback);
    hwTimerStarted = xTimerStart(highwaterTimer, 0 );

    // ...
}
