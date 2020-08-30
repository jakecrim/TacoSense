#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "transmission.h"

/* Defines */
// sizes
#define TRANSMIT_TASK_STACK_SIZE 10000
// priority levels
#define TRANSMIT_TASK_PRIO 1


/* Variables */
typedef struct transcieve_message {
	int distance;
} transcieve_message;



//Declarations
void wireless_Open(void);
esp_now_recv_cb_t receive_message(void);
esp_now_send_cb_t sent_message(void);
void receiveCallback(const uint8_t *macAddr, const uint8_t *data, int dataLen);
void transmit(transcieve_message data);
void tasks_Open();


int main(void)
{
	printf("TacoSense System Start: \n");
	tasks_Open();
	printf("[T] YO");
	transcieve_message message1;

	wireless_Open();
	for(;;)
	{
		delay(2500);
		message1.distance = 15;
		transmit(message1);
	}
}

void tasks_Open()
{
	xTaskCreate(vTransmitTask, "Transmit Task", TRANSMIT_TASK_STACK_SIZE, NULL, TRANSMIT_TASK_PRIO, NULL);
}

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

void transmit(transcieve_message data)
{
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

void transmit(const String &data)
{
	// Transmits to any device in range
	uint8_t transmitAddr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	esp_now_peer_info_t peer = {};
	memcpy(&peer.peer_addr, transmitAddr, 6);
	if (!esp_now_is_peer_exist(transmitAddr))
	{
		esp_now_add_peer(&peer);
	}
	esp_err_t result = esp_now_send(transmitAddr, (const uint8_t *)data.c_str(), data.length());
	// transmits to specific device
/*uint8_t peerAddress[] = {0x3C, 0x71, 0xBF, 0x47, 0xA5, 0xC0};
	esp_now_peer_info_t peerInfo = {};
	memcpy(&peerInfo.peer_addr, peerAddress, 6);
	if (!esp_now_is_peer_exist(peerAddress))
	{
	esp_now_add_peer(&peerInfo);
	}
	esp_err_t result = esp_now_send(peerAddress, (const uint8_t *)message.c_str(), message.length());*/
	if (result == ESP_OK)
	{
		Serial.println("Transmit success");
	}
	else if (result == ESP_ERR_ESPNOW_NOT_INIT)
	{
		Serial.println("ESPNOW not Initialized.");
	}
	else if (result == ESP_ERR_ESPNOW_ARG)
	{
		Serial.println("Invalid Arg");
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
		Serial.println("Peer was not found.");
	}
	else
	{
		Serial.println("Unknown error");
	}
}


void receiveCallback(const uint8_t *macAddr, const uint8_t *data, int dataLen)
{
	transcieve_message recieved;
	memcpy(&recieved, data, sizeof(data));
	printf("Bytes Recieved: %d \n", dataLen);

	printf("Distance: %d \n", recieved.distance);
}

//  to be used later as cb func for sending
// esp_now_send_cb_t sent_message()
// {

// }



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