#include "blink.h"

// define global variables for led status
int greenLED = 0;  // 0-off, 1-on
int redLED = 0;
int blueLED = 0;
int pinButton = 23; //GPIO pin used for pushbutton

// define pointers to pass to tasks to update led status
int *greenPtr = &greenLED;  
int *redPtr = &redLED;
int *bluePtr = &blueLED;
float speedMult = 1.0; // define speed multipier value

// load up data for each LED task
static BlinkData blinkGreen = { 25, 2500, &speedMult, &greenLED };
static BlinkData blinkRed  = { 27, 3300, &speedMult, &redLED };
static BlinkData blinkBlue = { 26, 1800, &speedMult, &blueLED };

// set up task handles for the RTOS tasks
TaskHandle_t taskGreen, taskRed, taskBlue;
TaskHandle_t taskSpeed;

// define function for highwater mark
UBaseType_t uxTaskGetStackHighWaterMark(TaskHandle_t xTask);

// define ISR routine to service button interrupt
void IRAM_ATTR buttonPush() {
  vTaskResume(taskSpeed); // run the speed program once
}

void TaskSpeed(void *pvParameters) {
  vTaskSuspend(NULL); // start in suspended state
  for(;;){
    speedMult = 0.667 * speedMult; // increase speed by 50% by cutting cycle time by 1/3
    Serial.println("Speed increased");
    vTaskSuspend(NULL); // run this task only once
  }
}

void main() 
{ 
    Serial.begin(115200);

    // setup button for interupt processing
    pinMode(pinButton, INPUT_PULLUP);
    attachInterrupt(pinButton, buttonPush, FALLING); 

    xTaskCreate (TaskBlink, "blabla", 4096, (void *)&blinkRed, 2, &taskRed);
    xTaskCreate (TaskBlink, "blabla", 4096, (void *)&blinkBlue, 2, &taskBlue);
    xTaskCreate (TaskBlink, "blabla", 4096, (void *)&blinkGreen, 2, &taskGreen);
    xTaskCreate (TaskSpeed, "Speed", NULL, 2, &taskSpeed); 

    //...
}