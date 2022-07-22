#include "distance_sensor_interface.h"
#include "settings.h"
int main(){
    char* portName = "\\\\.\\COM20";
    IdistanceSensor testSensor(1, new keyence::keyenceWinRS232(portName));
}