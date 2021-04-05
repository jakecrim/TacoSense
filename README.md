# TacoSense
> **W.I.P.** This software works directly with the 'VeHub' project to visualize the sensor data generated and transmitted by this software.


## Motivation
After 3 years of driving a long bed truck, I am pretty good at moving around town and obstacles even though it is larger than the average vehicle, but I continue to struggle with squeezing into tight spaces especially when backing up and having to estimate how close I can get to another vehicle. It also seemed useful to have a better idea of how far I am from objects in the front. Since this truck had no backup camera, I decided to outfit the truck with ultrasonic sensors and incorporate it in an IoT system. 

The system also has ultrasonic sensors in the front-left and front-right corner of the vehicle. This gives some added functionality for having an idea of your distance from possible other difficult to see areas. These combined four sensors provide an added benefit of assisting when navigating tight off-road terrain.

# Usage
Two different pieces of software
* TacoSense (THIS REPO): Actual Sensor handling and data transmission software
* VeHub (https://github.com/jakecrim/VeHub): W.I.P. Vehicle Hub Software, main hub for linking any sort of IoT vehicle additions together and visualizing necessary components **ex:** the TacoSense project.
---
Implementation
* Ultrasonic distance sensors are placed at the front left, front middle, front right, and rear of the vehicle.
* The ESP32 microcontroller (uC) forms a wireless connection via 'ESP-NOW' wireless protocol created by the ESP32 uC company espressif.
* W.I.P. more to be added...






