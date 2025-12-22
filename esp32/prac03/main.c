#include "../blink.h"

TaskHandle_t taskGreen, taskRed, taskBlue;
TaskHandle_t taskSpeed;
TaskHandle_t taskTally;

void TaskOLED() {
  char colorStr[6] ;
  for(;;) {
    if (redLED == 1) strcpy(colorStr,"Red");
    else if (greenLED == 1) strcpy(colorStr,"Green");
    else if (blueLED == 1) strcpy(colorStr,"Blue ");
    Display.println(colorStr);
    //Display.println(String(numLit));
    Display.display();
    // short unblocked delay between readings (1/10 second)
    vTaskDelay(100);
  }
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

  Blink_Init();

  xTaskCreate (TaskBlinkSeq, "", 4096, (void *)&blinkRed, 3, &taskRed);
  xTaskCreate (TaskBlinkSeq, "", 4096, (void *)&blinkBlue, 3, &taskBlue);
  xTaskCreate (TaskBlinkSeq, "", 4096, (void *)&blinkGreen, 3, &taskGreen);
  xTaskCreate (TaskSpeed, "Speed", NULL, 2, &taskSpeed); 
  xTaskCreate (TaskOLED, "OLED", NULL, 2, &taskTally); 

  // ...
}

