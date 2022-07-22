#include "distance_sensor_interface.h"
#include "settings.h"
int main(){

    IdistanceSensor testSensor(1, new keyence::keyenceWinRS232());
}