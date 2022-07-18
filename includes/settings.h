/**
 * @file settings.h
 * @author sami dhiab (sami@theion.de)
 * @brief settings framework, keyence api
 * @version 0.1
 * @date 2022-06-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/********** Keyence Specification *******/
#define NUM_OUTPUT_HEADS 3  //number of sensors output heads
#define COMMUNICATION_TYPE RS232 //define the rs232 interface
//#define COMMUNICATION_TYPE ETHERNET //define the ethernet interface
#if COMMUNICATION_TYPE == RS232
#define COMMUNICATION_HANDLER KEYENCE_SERIAL_HANDLER //define the serial handler
#define KEYENCE_SERIAL_BAUDRATE 115200
// these pins are reserved on esp32
// #define RX1_PIN 18
// #define TX1_PIN 19
#define PARITY SERIAL_8N1
#endif
/********* Mocking sensor *************/
#define ENABLE_MOCK_SERIAL true
/********** Framework Specification *******/
/**** AVR****
#if defined(__AVR__)
#include "Arduino.h"
#define string String
#define KEYENCE_SERIAL_HANDLER HardwareSerial(0)
#define USB_SERIAL HardwareSerial(2)
#endif
*/
/********** ESP32********/
#if defined(ESP32)
#define FRAMEWORK ARDUINO 
//#define FRAMEWORK ESP_IDF
#if FRAMEWORK==ARDUINO
#include "Arduino.h"
#include <HardwareSerial.h>
#define string String 
#define _VIRTUAL_TEST_
#define USB_SERIAL Serial
#define KEYENCE_SERIAL_HANDLER Serial2
#if ENABLE_MOCK_SERIAL == true
#define MOCK_SERIAL Serial
#endif
#endif
#endif

/********** Native cpp********/
/* by native cpp we want to skip any data forwarding controller (like arduino or esp32)
and directly interface the keyence controller via serial communication on WIN or UNIX OS*/
#define NATIVE
#if defined(NATIVE)
#define FRAMEWORK ARDUINO 
#define string std::string 
#define _VIRTUAL_TEST_
#define USB_SERIAL Serial
#define KEYENCE_SERIAL_HANDLER Serial2
#if ENABLE_MOCK_SERIAL == true
#define MOCK_SERIAL Serial
#endif
#endif