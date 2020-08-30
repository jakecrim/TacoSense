#include "transmission.h"
void vTransmitTask(void * parameter)
{
	for(;;)
	{
		vTaskDelay(1000);
		printf("Inside transmission task \n");
	}
	vTaskDelete(NULL);
}