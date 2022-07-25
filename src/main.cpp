#include "distance_sensor_interface.h"
int main(){
    const char* portName = "COM20";
    IdistanceSensor testSensor(1, new keyence::keyenceWinRS232(portName));
}