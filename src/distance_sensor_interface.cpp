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

IdistanceSensor::IdistanceSensor(int OutputHeadNumber, keyence::IkeyenceBase* InterfaceKeyence):HeadNum(OutputHeadNumber), keyenceInterface(InterfaceKeyence) {}
IdistanceSensor::~IdistanceSensor()
{
    delete keyenceInterface;
}
void IdistanceSensor::initSensorCom()
{
    keyenceInterface->initKeyenceCom();
    keyenceInterface->setGeneralMode();
}
double IdistanceSensor::getCurrentDistance()
{
    /******* get values from keyence *********/
    return currentDistance=keyenceInterface->getValueSingleOutputHead(HeadNum);
    //return currentDistance=KeyenceObject->getValueMultipleOutputHead("100000000000")[HeadNum-1];

}
void IdistanceSensor::printDistance(float val)
{
    USB_SERIAL.print("current distance head ");
    USB_SERIAL.print(this->HeadNum);
    USB_SERIAL.print(" equal to ");
    USB_SERIAL.println(val);
}
