#include "../blink.h"

TaskHandle_t taskTally;
TaskHandle_t taskHighwater;

void main() 
{ 
    Serial.begin(115200);

    //...

    xTaskCreate (TaskOLED, "Speed", NULL, 2, &taskTally); 
    xTaskCreate (TaskHighWater, "Speed", NULL, 2, &taskHighwater); 
    //...
}
