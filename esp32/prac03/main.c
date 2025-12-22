#include "../blinking.h"

//define semaphore object handle
SemaphoreHandle_t syncFlag;

void main() 
{ 
  Serial.begin(115200);

  // create the binary semaphore
  syncFlag = xSemaphoreCreateBinary();
  if (syncFlag != NULL){
    println("flag OK");
  }
    xTaskCreate (TaskBlinkSeq, "blabla", 4096, (void *)&blinkGreen, 2, &taskGreen);
    xTaskCreate (TaskSpeed, "Speed", NULL, 2, &taskSpeed); 

}

