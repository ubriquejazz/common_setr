#ifndef BLINKING_H
#define BLINKING_H

// define structure for data to pass to each task
struct BlinkData {
  int pin;
  int delay;
  float *speedMult;
  int *status;
};

// define task functions
void TaskBlink(void *pvParameters);
void TaskBlinkSeq(void *pvParameters);

#endif