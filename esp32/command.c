#include "command.h"
#include <string.h>

// define global variables to hold the parsed input data
char cmdFromPC[numChars] = {0};
char objFromPC[numChars] = {0};

SemaphoreHandle_t printMutex;
BaseType_t newData = pdFALSE;
char receivedChars[numChars];
char tempChars[numChars]; // temporary array for use when parsing

void recvWithEndMarker() 
{
    static byte ndx = 0;
    char endMarker = '\n';
    
    while (Serial.available() > 0 && newData == pdFALSE) {
        char rc = Serial.read();
        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = pdTRUE;
        }
    }
}

void parseData() {     // split the data into its parts
    char * strtokIndx; // this is used by strtok() as an index
    strtokIndx = strtok(tempChars," "); // get the first part - the string
    strcpy(cmdFromPC, strtokIndx); // copy it to cmdFromPC

    strtokIndx = strtok(NULL, " "); // this continues where the previous call left off
    strcpy(objFromPC, strtokIndx);  // copy it to objFromPC
}

void checkParsedData()
{
    // *** 3 *** take the printer mutex
    xSemaphoreTake(printMutex, portMAX_DELAY);
    char * cmd;
    char * obj;
    int validRequest = 0;
    cmd = strstr(cmdList, cmdFromPC);

    if (cmd){
        validRequest += 1;
    } else {
        Serial.println("rejected - unrecognized command");
        validRequest -= 1;
    }

    if (strstr("speed",cmdFromPC)){
        obj = strstr(objListSpeed,objFromPC);
        if (obj)    {
            validRequest += 1;
        } else {
            Serial.println("rejected - unrecognized request");
            validRequest -= 1;
        }
    } else {
        obj = strstr(objListLED,objFromPC);
        if (obj)  {
          validRequest  += 1;
        } else {
          Serial.println("rejected - unrecognized request");
          validRequest -= 1;
        }
    }

    if (validRequest == 2){
        Serial.println("command accepted");
        Serial.println(String(cmdFromPC) + "  " + String(objFromPC));
    }
    Serial.flush();
    vTaskDelay(pdMS_TO_TICKS(3000));  // *** 4 *** flush the print data and wait three seconds for the user to read the response
    xSemaphoreGive(printMutex);
}