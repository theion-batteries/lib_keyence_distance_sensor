/**
 * @file IdistanceSensor.hpp
 * @author sami dhiab (sami@theion.de)
 * @brief interface wrapper distance sensor
 * @version 0.1
 * @date 2022-02-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "distance_sensor_interface.h"


// conctructor distance sensor generic keyence
// 1 - 12
IdistanceSensor::IdistanceSensor(int OutputHeadNumber)
{
this->HeadNum=OutputHeadNumber;
}
IdistanceSensor::~IdistanceSensor()
{
    delete KeyenceObject;
}
void IdistanceSensor::initSensorCom()
{
    KeyenceObject->initKeyenceCom();
    KeyenceObject->setGeneralMode();
}

// generic methods
double IdistanceSensor::getCurrentDistance()
{
    /******* get values from keyence *********/
    return currentDistance=KeyenceObject->getValueSingleOutputHead(this->HeadNum);
}
void IdistanceSensor::printDistance(float val)
{
    SERIAL_HANDLER.PRINT("current distance head ");
    SERIAL_HANDLER.PRINT(this->HeadNum);
    SERIAL_HANDLER.PRINT(" equal to ");
    SERIAL_HANDLER.PRINT_NEW_LINE(val);
}
