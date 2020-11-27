#include <stdio.h>
#include <Arduino.h>

/* Defines */
// Trigger Pin Front Sensor 1
#define TRIG_F1 23
#define TRIG_F2 19
#define TRIG_F3 17

#define ECHO_F1 22
#define ECHO_F2 18
#define ECHO_F3 16

// Declarations
void sensors_Open(void);
void vSensorTask(void * parameter);
int senseDistance(int);
