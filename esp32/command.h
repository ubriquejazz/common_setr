#ifndef CMD_H
#define CMD_H

const byte numChars = 24;
 
struct CMD_Data {
  char  Cmd[numChars];
  char  Obj[numChars];
};

void CMD_Init();
void CMD_Exec(void *pvParameter);
void CMD_Parse(void *pvParameter);

#endif