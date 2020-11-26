#include "sensors.h"
#include "transmission.h"

void sensors_Open()
{
	printf("Initializing Hardware: \n");
}

void vSensorTask(void * parameter)
{
	transcieve_message * messageShared = (transcieve_message *)parameter;
	for(;;)
	{
		printf("sEnSInG sTuFf \n");
		vTaskDelay(8500 / portTICK_PERIOD_MS);
		messageShared->distance1 = 420;
	}
}