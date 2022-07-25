#include "distance_sensor_interface.h"
int main(){
    const char* portName = "COM20"; //com port on windows
    IdistanceSensor testSensor(1, new keyence::keyenceWinRS232(portName)); // instance sensor
    testSensor.initSensorCom(); // init sensor communication
    testSensor.getCurrentDistance(); // get sensor mesured data
}