// General Configuration and Identification for each TacoSensor Device

/* Defines */
// TASK RELATED
// sizes
#define TRANSMIT_TASK_STACK_SIZE 10000
#define SENSOR_TASK_STACK_SIZE 10000
// priority levels
#define TRANSMIT_TASK_PRIO 2 
#define SENSOR_TASK_PRIO 1

// Choose Device Front or Rear
#define DEVICE_FRONT 1
#define DEVICE_REAR 0

#define DEBUG 0