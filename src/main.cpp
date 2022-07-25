#include "distance_sensor_interface.h"
int main(){
    const char* portName = "COM20";
    keyence::IkeyenceRS232* keyenceInterfaceRs232 =  new keyence::keyenceWinRS232(portName);
   // IdistanceSensor testSensor(1, keyenceInterfaceRs232);
}