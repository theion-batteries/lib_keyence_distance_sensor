#include "distance_sensor_interface.h"
int main(){
    const char* ip = "192.168.0.104"; //ip controller
    uint16_t port = 12345; // port
    IdistanceSensor testSensor(1, new keyence::keyenceWinSocket(ip, port)); // instance sensor
    testSensor.initSensorCom(); // init sensor communication
    //testSensor.getCurrentDistance(); // get sensor mesured data
}