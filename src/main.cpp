#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "transmission.h"
#include "sensors.h"
#include "TSconfig.h"

/* Variables */


//Declarations
esp_now_recv_cb_t receive_message(void);
esp_now_send_cb_t sent_message(void);
void transmit(transcieve_message data);
void tasks_Open();


// Scheduling the tasks 
void tasks_Open(transcieve_message * messageShared)
{
	// shared message between threads
	// transcieve_message messageShared;
	messageShared->distance1 = 69;
	xTaskCreate(vTransmitTask, "Transmit Task", TRANSMIT_TASK_STACK_SIZE, (void *) messageShared, TRANSMIT_TASK_PRIO, NULL);
	xTaskCreate(vSensorTask, "Sensor Task", SENSOR_TASK_STACK_SIZE, (void *) messageShared, SENSOR_TASK_PRIO, NULL);
}

int main(void)
{
	printf("TacoSense System Start: \n");
	transcieve_message messageShared;
	sensors_Open();
	wireless_Open();
	tasks_Open(&messageShared);
	for(;;)
	{
		delay(10000);
		printf("Scheduled FreeRTOS Tasks Running... \n");
	}
}



void setup() 
{
	Serial.begin(115200);
	delay(1000);
	main();
}

void loop() 
{
	Serial.println("YOOOO");
	delay(1000);
}