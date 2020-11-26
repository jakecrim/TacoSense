#include "transmission.h"
#include "sensor.h"

// Main Transmitting Task
void vTransmitTask(void * parameter)
{
	// message structure instance
	transcieve_message * messageShared = (transcieve_message *)parameter;
	printf("Message shared print test: %d \n", messageShared->distance1);
	for(;;)
	{
		vTaskDelay(2500 / portTICK_PERIOD_MS);
		printf("Transmitting data: \n");
		// routinely transmitting the shared message that has the distance values updated by various sensor tasks
		transmit(*(messageShared));
	}
	vTaskDelete(NULL);
}

void transmit(transcieve_message data)
{
	printf("data is %d \n", data.distance1);
	printf("device num is %d \n", data.deviceNum);
	// Transmits to any device in range
	uint8_t transmitAddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	esp_now_peer_info_t peer = {};
	memcpy(&peer.peer_addr, transmitAddr, 6);
	if (!esp_now_is_peer_exist(transmitAddr))
	{
		esp_now_add_peer(&peer);
	}
	esp_err_t result = esp_now_send(transmitAddr, (uint8_t *) &data , sizeof(data));

	if (result == ESP_OK)
	{
		Serial.println("Broadcast message success");
	}
	else if (result == ESP_ERR_ESPNOW_NOT_INIT)
	{
		Serial.println("ESPNOW not Init.");
	}
	else if (result == ESP_ERR_ESPNOW_ARG)
	{
		Serial.println("Invalid Argument");
	}
	else if (result == ESP_ERR_ESPNOW_INTERNAL)
	{
		Serial.println("Internal Error");
	}
	else if (result == ESP_ERR_ESPNOW_NO_MEM)
	{
		Serial.println("ESP_ERR_ESPNOW_NO_MEM");
	}
	else if (result == ESP_ERR_ESPNOW_NOT_FOUND)
	{
		Serial.println("Peer not found.");
	}
	else
	{
		Serial.println("Unknown error");
	}
}


// When a message comes in from ESP-NOW, this called and makes a call to handle the correct lighting and display info
void receiveCallback(const uint8_t *macAddr, const uint8_t *data, int dataLen)
{
	transcieve_message recieved;
	memcpy(&recieved, data, sizeof(data));
	printf("Bytes Recieved: %d \n", dataLen);

	printf("Received Distance: %d \n", recieved.distance1);
}

// ESP-NOW Configuration and registration
void wireless_Open()
{
	WiFi.mode(WIFI_STA);
	Serial.print("Station Mode: \n");
	Serial.println("MAC Addr: ");
	Serial.print(WiFi.macAddress());
	WiFi.disconnect();
	if (esp_now_init() == ESP_OK)
	{
		printf("\n ESP-NOW Initialized \n");
		esp_now_register_recv_cb(receiveCallback);
		// esp_now_register_send_cb(sent_message);
	}
	else
	{
		printf("ESP-NOW Init Failed...restarting \n");
		delay(500);
		ESP.restart();
	}
	
}