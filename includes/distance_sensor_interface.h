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
#pragma once
#include "settings.h"
class IdistanceSensor
{
    public:
    ~IdistanceSensor();
    IdistanceSensor(int OutputHeadNumber, keyence::IkeyenceBase* keyenceInterface);
    void initSensorCom();
    //generic methods
    double getCurrentDistance();
    void printDistance(float val);
    private:
    keyence::IkeyenceBase* keyenceInterface; // pointer to the interface
    int Pin;
    bool state;
    double currentDistance;
    int HeadNum;

};