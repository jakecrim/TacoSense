#include "sensors.h"
#include "transmission.h"

// variables
static portMUX_TYPE senseMutex;

void sensors_Open(void * parameter)
{
	transcieve_message * messageShared = (transcieve_message *)parameter;

	printf("Initializing Sensor Hardware: \n");
	pinMode(TRIG_F1, OUTPUT);
	pinMode(ECHO_F1, INPUT);
	pinMode(TRIG_F2, OUTPUT);
	pinMode(ECHO_F2, INPUT);	
	pinMode(TRIG_F3, OUTPUT);
	pinMode(ECHO_F3, INPUT);
	
	// initialize mutex
	vPortCPUInitializeMutex(&senseMutex);

	#ifdef DEVICE_FRONT
		messageShared->deviceNum = 1;
	#endif

	#ifdef DEVICE_BACK
		messageShared->deviceNum = 2;
	#endif

}

// void vSensorTask(void * parameter)
// {
// 	transcieve_message * messageShared = (transcieve_message *)parameter;

// 	for(;;)
// 	{
// 		vTaskDelay(250 / portTICK_PERIOD_MS);
// 		#ifdef DEVICE_FRONT
// 			messageShared->deviceNum = 1;
// 			messageShared->distance1 = senseDistance(1);
// 			vTaskDelay(2 / portTICK_PERIOD_MS);
// 			messageShared->distance2 = senseDistance(2);
// 			vTaskDelay(2 / portTICK_PERIOD_MS);
// 			messageShared->distance3 = senseDistance(3);
// 		#endif
// 	}
// }

void vSensorFLTask(void * parameter)
{
	transcieve_message * messageShared = (transcieve_message *)parameter;

	for(;;)
	{
		vTaskDelay(250 / portTICK_PERIOD_MS);
		// enter critical
		portENTER_CRITICAL(&senseMutex);
			messageShared->distance1 = senseDistance(1);
		// exit critical
		portEXIT_CRITICAL(&senseMutex);
	}
}

void vSensorFMTask(void * parameter)
{
	transcieve_message * messageShared = (transcieve_message *)parameter;

	for(;;)
	{
		vTaskDelay(250 / portTICK_PERIOD_MS);
		// enter critical
		portENTER_CRITICAL(&senseMutex);
			messageShared->distance2 = senseDistance(2);
		// exit critical
		portEXIT_CRITICAL(&senseMutex);
	}
}

void vSensorFRTask(void * parameter)
{
	transcieve_message * messageShared = (transcieve_message *)parameter;

	for(;;)
	{
		vTaskDelay(250 / portTICK_PERIOD_MS);
		// enter critical
		portENTER_CRITICAL(&senseMutex);
			messageShared->distance3 = senseDistance(3);
		// exit critical
		portEXIT_CRITICAL(&senseMutex);
	}
}

int senseDistance(int sensorID)
{
	uint64_t pulseTime = 0;
	uint32_t distance = 0;
	int trigPin = 0;
	int echoPin = 0;

	// Choose which sensor pins to set high/low
	if(sensorID == 1)
	{
		trigPin = TRIG_F1;
		echoPin = ECHO_F1;
	}
	else if(sensorID == 2)
	{
		trigPin = TRIG_F2;
		echoPin = ECHO_F2;
	}
	else if(sensorID == 3)
	{
		trigPin = TRIG_F3;
		echoPin = ECHO_F3;
	}

	// Make sure the TRIG pin is clear
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	// Generate ultrasonic pulse for 10 us
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	// return travel time of the pulse to the object and back in us
	pulseTime = pulseIn(echoPin, HIGH);

	// calculating distance
	distance = pulseTime*0.034 / 2 ;
	#if DEBUG
		printf("Distance for ID %d is: %d \n", sensorID, distance);
	#endif
	return distance;
}