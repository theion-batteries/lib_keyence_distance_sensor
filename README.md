# lib_keyence_distance_sensor

* Author: Sami Dhiab<br>

* Version: 1.0

## Introduction
This Repo include standalone cpp library for interfacing the keyence controll unitusing the interface class distance_sensor.
This library is designed to be system independant and uses the dependencies injection mechanism to include the correct class.

## APIs
To use this library, create an instance of the distance sensor by injecting the correct interface (communication -> architecture).
Example:
~~~cpp
// create a distance sensor object on windows machine using the rs232 communication 
const char* portName = "COM20"; //com port on windows
IdistanceSensor testSensor(1, new keyence::keyenceWinRS232(portName)); // instance sensor
~~~
initialise the sensor as follow:
~~~cpp
testSensor.initSensorCom(); // init sensor communication
~~~
read data from sensor as follow:
~~~cpp
testSensor.getCurrentDistance(); // get sensor mesured data
~~~
## Build
use the provided [build](build_script.bat) script or cmake file to build the project and run it.

## Unit Tests
This library has a mock implementation to test all sensor responses and the programm logic on esp32 mcu.
The same testing procedure can be applied on any platform.
please follow the link for full virtual implementation:
https://wokwi.com/projects/334545131093885522
