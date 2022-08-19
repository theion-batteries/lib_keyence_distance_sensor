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
#include "keyence_rs232_api.h"
#include "keyence_win_api.h"
class IdistanceSensor
{
public:
    IdistanceSensor(int OutputHeadNumber, keyence::IkeyenceBase* keyenceInterface);
    virtual ~IdistanceSensor();
    void initSensorCom();
    //generic methods
    double getCurrentDistance();
    std::vector<double> getValuesAll();
    void printDistance(float val);
    
private:
    keyence::IkeyenceBase* keyenceInterface; // pointer to the interface
    int Pin;
    bool state;
    double currentDistance;
    int HeadNum;
    

};