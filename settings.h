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

#pragma once



/********** Keyence Specification *******/
#define NUM_OUTPUT_HEADS 3  //number of sensors output heads
#define COMMUNICATION_TYPE RS232 //define the rs232 interface
//#define COMMUNICATION_TYPE ETHERNET //define the ethernet interface
#if COMMUNICATION_TYPE == RS232
#define COMMUNICATION_HANDLER SERIAL_HANDLER //define the serial handler
#define KEYENCE_SERIAL_BAUDRATE 115200
#endif
#define PRINT_NEW_LINE
#define PRINT
/********** Framework Specification *******/
#define __AVR__
#if defined(__AVR__)
#include "Arduino.h"
#define std::string String
#define SERIAL_HANDLER Serial1
#define PRINT_NEW_LINE println
#define PRINT print
#define BEGIN begin
#define AVAILABLE available
#elif defined(ESP8266)

#elif defined(ESP32)
#include "Arduino.h"
#define std::string String
#define SERIAL_HANDLER Serial1
#define PRINT_NEW_LINE println
#define PRINT print
#endif
