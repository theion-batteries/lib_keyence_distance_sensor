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
Keyence_base::HeadsArray[Keyence_base::HeadsCount]=OutputHeadNumber;
Keyence_base::HeadsCount++;
}
~IdistanceSensor()
{
    delete KeyenceObject;
}
void IdistanceSensor::initSensorCom()
{
    IkeyenceRS232->initKeyenceCom();
    IkeyenceRS232->setGeneralMode();
}

// generic methods
double IdistanceSensor::getCurrentDistance()
{
    /******* get values from keyence *********/
    IkeyenceRS232->getValueOutputHeadAll();
    return Keyence_base::LookUpValues[this->HeadNum-1];
}
void IdistanceSensor::printDistance(float val)
{
    Serial.print("current distance head ");
    Serial.print(this->HeadNum);
    Serial.print(" equal to ");
    Serial.println(val);
}
