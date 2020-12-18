// General Configuration and Identification for each TacoSensor Device

/* Defines */
// TASK RELATED
// sizes
#define TRANSMIT_TASK_STACK_SIZE 10000
#define SENSOR_TASK_STACK_SIZE 10000
// priority levels
#define TRANSMIT_TASK_PRIO 6 
#define SENSOR_TASK_PRIO 5

// Choose Device Front or Rear
#define DEVICE_FRONT 0
#define DEVICE_BACK 1

#define DEBUG 0