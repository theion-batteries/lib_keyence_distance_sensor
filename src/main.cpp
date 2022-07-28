#include "distance_sensor_interface.h"
int main(){
    std::map<std::string, std::map<std::string, uint16_t> > ip_port_map;
    ip_port_map["oscilloscop"]["192.168.0.105"]=3000;
    ip_port_map["delta"]["192.168.0.201"]=3344;
    ip_port_map["keyence"]["192.168.0.104"]=3000;
    const char* ip = "192.168.0.105"; //ip controller
    uint16_t port = 3000; // port
    IdistanceSensor testSensor(1, new keyence::keyenceWinSocket(ip, port)); // instance sensor
    testSensor.initSensorCom(); // init sensor communication
    //testSensor.getCurrentDistance(); // get sensor mesured data
}