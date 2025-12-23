#ifndef CMD_H
#define CMD_H

const byte numChars = 24;
 
struct CmdData {
  char  Cmd[numChars];
  char  Obj[numChars];
};

const char* cmdList = "kill...pause...resume...speed"; // list of accepted values for command
const char* objListLED = "red...green...blue";   // list of accepted values 
const char* objListSpeed = "faster...slower";

void recvWithEndMarker();
void parseData(); // split the data into its parts
void checkParsedData();

#endif