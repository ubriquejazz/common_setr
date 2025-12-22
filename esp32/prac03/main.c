#include "../command.h"

TaskHandle_t taskCmdParse, taskCmdExec;
TaskHandle_t taskCmd = NULL; // task handle used to pause, restart, or stop running tasks


void main() 
{ 
    Serial.begin(115200);

    //...

  // Run this in core separate from LED tasks if there are two cores. Still priority 2
  xTaskCreate( TaskCmdParse, "Command Parser", 4096, NULL, 2, &taskCmdParse); 
    
  xTaskCreate( TaskCmdExec, "Execute Commands From Queue", 4096, NULL, 2, &taskCmdExec); 

    //...
}

