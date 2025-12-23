#include "command.h"
#include <string.h>

// define mutex object handle
SemaphoreHandle_t printMutex;

// define the queue handle for the queCmd queue
QueueHandle_t queCmd;

// command and object
CMD_Data valueToSend;

const char* cmdList = "kill...pause...resume...speed"; // list of accepted values for command
const char* objListLED = "red...green...blue";   // list of accepted values 
const char* objListSpeed = "faster...slower";

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

void checkParsedData() {
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

void CMD_Init() {
    // start printer mutex access
    printMutex = xSemaphoreCreateMutex();
    if (printMutex != NULL) Serial.println("printMutex created");

    // initialize queue for commands
    queCmd = xQueueCreate( 5, sizeof(CMD_Data) );
    if( queCmd != NULL ) Serial.println("command queue created");

    strcpy(valueToSend.Cmd, "");
    strcpy(valueToSend.Obj, "");
}

void CMD_Exec(void *pvParameters) 
{
    (void)pvParameters;
    CMD_Data receivedValue;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS( 100 );
    char nameObj[8];

    for(;;) {
    xStatus = xQueueReceive( queCmd, &receivedValue, xTicksToWait );
    if( xStatus == pdPASS )
      {
      xSemaphoreTake(printMutex,portMAX_DELAY);  // get the printer mutex for use of the printer
      // check which led color to modify and set approriate task
      if (strstr("red",receivedValue.Obj))
        {
        strcpy(nameObj,"red");
        taskCmd = taskRed;
        }
      else if (strstr("green",receivedValue.Obj))
        {strcpy(nameObj,"green");
        taskCmd = taskGreen;}
      else if (strstr("blue",receivedValue.Obj)) 
        {strcpy(nameObj,"blue");
        taskCmd = taskBlue;}

      // check which command is sent and respond accordingly
      if (strstr("pause",receivedValue.Cmd)) 
        {
        vTaskSuspend(taskCmd);
        Serial.print(nameObj);
        Serial.println(" paused");
        }
      else if (strstr("resume",receivedValue.Cmd))
        {
          vTaskResume(taskCmd);
          Serial.print(nameObj);
          Serial.println(" resumed");
        }  
      else if (strstr("kill",receivedValue.Cmd))
              {
                vTaskDelete(taskCmd);
                Serial.print(nameObj);
                Serial.println(" killed");
        }
      else if (strstr("speed" , receivedValue.Cmd) ) 
        {
          if (strstr ( "slower" , receivedValue.Obj))
            {speedMult *= 1.5;
            Serial.println("speed is slower");}
          else if (strstr("faster" , receivedValue.Obj)) 
            {speedMult *= 0.67;
            Serial.println("speed is faster");} 
        }
      Serial.flush(); 
      vTaskDelay(pdMS_TO_TICKS(5000)); 
      xSemaphoreGive(printMutex);   
    } 
    else {
      /* Do nothing here - Wait for a new entry to be added into the command queue */
      }
    }
}

void CMD_Parse(void *pvParameters)  // This is a task template
{
  // This uses non-blocking input routines to read and check user input
  // If values are acceptable the command is sent to the command processor
  // The input format is "command object" where command and object must conform
  // to values in lists.  If either is not valid the user is notified. 

  // define sub functions used here
  (void)pvParameters;
    void parseData(void); // split the data into its parts
    void checkParsedData(void);
    void recvWithEndMarker(void);

  for(;;)  // A Task shall never return or exit. 
  {
    BaseType_t xStatus;  // *** 1 *** typedef statement
    
    recvWithEndMarker();
    if (newData == pdTRUE) {
      strcpy(tempChars, receivedChars);
      strcat (tempChars, " 1 2 3"); //add spaces in case user didn't enter any
        // this temporary copy is necessary to protect the original data
        //   because strtok() used in parseData() replaces the commas with \0
      parseData();
      checkParsedData();
      newData = pdFALSE;

      // load values into the struct used to send message in queue and send
      strcpy(valueToSend.Cmd, cmdFromPC);
      strcpy(valueToSend.Obj, objFromPC);
      // *** 2 *** add the input values to the back of the queue
      xStatus = xQueueSendToBack( queCmd, &valueToSend, 0 );
        if( xStatus != pdPASS ) {Serial.println("queue send failed!");}
    } 
  }
}