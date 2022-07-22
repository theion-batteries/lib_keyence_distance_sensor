/**
 * @file IdistanceSensor.hpp
 * @author sami dhiab (sami@theion.de)
 * @brief mock of sensor response
 * @version 0.1
 * @date 2022-02-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "settings.h"
#include "keyence_arduino_api.h"
/*
* The sensor mock will respond to any message coming from real sensor
* sensor mock will use serial 2, real sensor serial 1 and output on serial 0
*/
class SensorMock: public keyence::KeyenceToArduino
{
public:
void initMock() {
    MOCK_SERIAL.begin(115200);
}
void injectCustomResponse(const string& response ) {
    MOCK_SERIAL.println(response);
}
};