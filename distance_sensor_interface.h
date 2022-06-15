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
#include "keyence_api.h"
class IdistanceSensor
{
    public:
    IkeyenceRS232* KeyenceObject = new IkeyenceRS232();
    ~IdistanceSensor();
    int Pin;
    bool state;
    double currentDistance;
    int HeadNum;
    IdistanceSensor(int OutputHeadNumber);
    void initSensorCom();
    //generic methods
    double getCurrentDistance();
    void printDistance(float val);
};