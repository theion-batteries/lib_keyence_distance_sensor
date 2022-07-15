#include "distance_sensor_interface.h"
#include <unity.h>
#include "sensor_mock.h"

IdistanceSensor sensor(1);
IdistanceSensor sensor2(2);
IdistanceSensor sensor3(3);
SensorMock sensorMocker;
SensorMock sensorMocker2;
SensorMock sensorMocker3;

// response to test: head1
string Error1SensorResponse1="MS,01,0xFFFF\r";
string Error2SensorResponse1="MS,01,0xFFFFFFFF\r";
string ZeroSensorResponse1="MS,01,0\r";
string NegativSensorResponse1="MS,01,-150\r";
string GoodSensorResponse1="MS,01,150\r";
// response to test: head2
string Error1SensorResponse2="MS,02,0xFFFF\r";
string Error2SensorResponse2="MS,02,0xFFFFFFFF\r";
string ZeroSensorResponse2="MS,02,0\r";
string NegativSensorResponse2="MS,02,-100\r";
string GoodSensorResponse2="MS,02,100\r";
// response to test: head3
string Error1SensorResponse3="MS,03,0xFFFF\r";
string Error2SensorResponse3="MS,03,0xFFFFFFFF\r";
string ZeroSensorResponse3="MS,03,0\r";
string NegativSensorResponse3="MS,03,-200\r";
string GoodSensorResponse3="MS,03,200\r";

void setUp(void) {
    // set stuff up here
    //USB_SERIAL.begin(115200);
    sensor.initSensorCom();
    sensorMocker.initMock();
    sensor2.initSensorCom();
    sensorMocker2.initMock();
    sensor3.initSensorCom();
    sensorMocker3.initMock();
}

void tearDown(void) {
    // clean buffer
    USB_SERIAL.flush();
    MOCK_SERIAL.flush();
    KEYENCE_SERIAL_HANDLER.flush();
}
// 1 sensor
void test_good_response(void) {
    double value = 150;
    sensorMocker.injectCustomResponse(GoodSensorResponse1);
    TEST_ASSERT_EQUAL(value, sensor.getCurrentDistance());
}
//2 sensor
void test_good_response2(void) {
    double value = 100;
    sensorMocker2.injectCustomResponse(GoodSensorResponse2);
    TEST_ASSERT_EQUAL(value, sensor2.getCurrentDistance());
}
//3 sensor 
void test_good_response3(void) {
    double value = 200;
    sensorMocker3.injectCustomResponse(GoodSensorResponse3);
    TEST_ASSERT_EQUAL(value, sensor3.getCurrentDistance());
}
void test_error1_response(void) {
    //Serial.println("last value:"+string(sensor.KeyenceObject->lastValue));
    sensorMocker.injectCustomResponse(Error1SensorResponse1);
    //Serial.println("last value:"+string(sensor.KeyenceObject->lastValue));
    double value = sensor.KeyenceObject->lastValue;
    TEST_ASSERT_EQUAL(value, sensor.getCurrentDistance());
}
void test_error1_response2(void) {
    double value = sensor2.KeyenceObject->lastValue;
    //Serial.println("last value:"+string(sensor2.KeyenceObject->lastValue));
    sensorMocker2.injectCustomResponse(Error1SensorResponse2);
    //Serial.println("last value:"+string(sensor2.KeyenceObject->lastValue));
        TEST_ASSERT_EQUAL(value, sensor2.getCurrentDistance());
}
void test_error1_response3(void) {
    double value = sensor3.KeyenceObject->lastValue;
    //Serial.println("last value:"+string(sensor3.KeyenceObject->lastValue));
    sensorMocker3.injectCustomResponse(Error1SensorResponse3);
    //Serial.println("last value:"+string(sensor3.KeyenceObject->lastValue));
        TEST_ASSERT_EQUAL(value, sensor3.getCurrentDistance());
}
void test_error2_response(void) {
    double value = sensor.KeyenceObject->lastValue;
    sensorMocker.injectCustomResponse(Error1SensorResponse1);
    TEST_ASSERT_EQUAL(value, sensor.getCurrentDistance());
}
void test_error2_response2(void) {
    double value = sensor2.KeyenceObject->lastValue;
    sensorMocker2.injectCustomResponse(Error2SensorResponse2);
    TEST_ASSERT_EQUAL(value, sensor2.getCurrentDistance());
}
void test_error2_response3(void) {
    double value = sensor3.KeyenceObject->lastValue;
    sensorMocker3.injectCustomResponse(Error2SensorResponse3);
    TEST_ASSERT_EQUAL(value, sensor3.getCurrentDistance());
}
void test_zero_response(void) {
    double value =sensor.KeyenceObject->lastValue; 
       sensorMocker.injectCustomResponse(ZeroSensorResponse1);
    TEST_ASSERT_EQUAL(value, sensor.getCurrentDistance());
}
void test_injectedLastValue_ifError1Response(void) {
    sensor.KeyenceObject->lastValue=100;
    sensorMocker.injectCustomResponse(Error1SensorResponse1);
    double value =sensor.KeyenceObject->lastValue; 
    TEST_ASSERT_EQUAL(value, sensor.getCurrentDistance());
}
void test_injectedLastValue_ifError2Response(void) {
    double value =sensor.KeyenceObject->lastValue; 
    sensor.KeyenceObject->lastValue=100;
    sensorMocker.injectCustomResponse(Error2SensorResponse1);
    TEST_ASSERT_EQUAL(value, sensor2.getCurrentDistance());
}
void test_injectedLastValue_ifZeroResponse(void) {
    double value =sensor.KeyenceObject->lastValue; 
       sensor.KeyenceObject->lastValue=100;
    sensorMocker.injectCustomResponse(ZeroSensorResponse1);
    TEST_ASSERT_EQUAL(value, sensor.getCurrentDistance());
}
void test_negativeValue_response(void) {
    double value = -150;
    sensorMocker.injectCustomResponse(NegativSensorResponse1);
    TEST_ASSERT_EQUAL(value, sensor.getCurrentDistance());
}
void test_zero_response2(void) {
    double value =sensor.KeyenceObject->lastValue; 
       sensorMocker2.injectCustomResponse(ZeroSensorResponse2);
    TEST_ASSERT_EQUAL(value, sensor2.getCurrentDistance());
}
void test_injectedLastValue_ifError1Response2(void) {
    sensor2.KeyenceObject->lastValue=100;
    sensorMocker2.injectCustomResponse(Error1SensorResponse2);
    double value =sensor2.KeyenceObject->lastValue; 
    TEST_ASSERT_EQUAL(value, sensor2.getCurrentDistance());
}
void test_injectedLastValue_ifError2Response2(void) {
    double value =sensor2.KeyenceObject->lastValue; 
    sensor2.KeyenceObject->lastValue=100;
    sensorMocker2.injectCustomResponse(Error2SensorResponse2);
    TEST_ASSERT_EQUAL(value, sensor2.getCurrentDistance());
}
void test_injectedLastValue_ifZeroResponse2(void) {
    double value =sensor2.KeyenceObject->lastValue; 
       sensor2.KeyenceObject->lastValue=100;
    sensorMocker2.injectCustomResponse(ZeroSensorResponse2);
    TEST_ASSERT_EQUAL(value, sensor2.getCurrentDistance());
}
void test_negativeValue_response2(void) {
    double value = -100;
    sensorMocker2.injectCustomResponse(NegativSensorResponse2);
    TEST_ASSERT_EQUAL(value, sensor2.getCurrentDistance());
}
void test_zero_response3(void) {
    double value =sensor3.KeyenceObject->lastValue; 
       sensorMocker3.injectCustomResponse(ZeroSensorResponse3);
    TEST_ASSERT_EQUAL(value, sensor3.getCurrentDistance());
}
void test_injectedLastValue_ifError1Response3(void) {
    sensor3.KeyenceObject->lastValue=100;
    sensorMocker3.injectCustomResponse(Error1SensorResponse3);
    double value =sensor3.KeyenceObject->lastValue; 
    TEST_ASSERT_EQUAL(value, sensor3.getCurrentDistance());
}
void test_injectedLastValue_ifError2Response3(void) {
    double value =sensor3.KeyenceObject->lastValue; 
    sensor3.KeyenceObject->lastValue=100;
    sensorMocker3.injectCustomResponse(Error2SensorResponse3);
    TEST_ASSERT_EQUAL(value, sensor3.getCurrentDistance());
}
void test_injectedLastValue_ifZeroResponse3(void) {
    double value =sensor3.KeyenceObject->lastValue; 
       sensor3.KeyenceObject->lastValue=100;
    sensorMocker3.injectCustomResponse(ZeroSensorResponse3);
    TEST_ASSERT_EQUAL(value, sensor3.getCurrentDistance());
}
void test_negativeValue_response3(void) {
    double value = -200;
    sensorMocker3.injectCustomResponse(NegativSensorResponse3);
    TEST_ASSERT_EQUAL(value, sensor3.getCurrentDistance());
}
//void test_string_substring(void) {
//    TEST_ASSERT_EQUAL_STRING("Hello", STR_TO_TEST.substring(0, 5).c_str());
//}
//
//void test_string_index_of(void) {
//    TEST_ASSERT_EQUAL(7, STR_TO_TEST.indexOf('w'));
//}
//
//void test_string_equal_ignore_case(void) {
//    TEST_ASSERT_TRUE(STR_TO_TEST.equalsIgnoreCase("HELLO, WORLD!"));
//}
//
//void test_string_to_upper_case(void) {
//    STR_TO_TEST.toUpperCase();
//    TEST_ASSERT_EQUAL_STRING("HELLO, WORLD!", STR_TO_TEST.c_str());
//}
//
//void test_string_replace(void) {
//    STR_TO_TEST.replace('!', '?');
//    TEST_ASSERT_EQUAL_STRING("Hello, world?", STR_TO_TEST.c_str());
//}


void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_good_response);
    RUN_TEST(test_good_response2);
    RUN_TEST(test_good_response3);
    RUN_TEST(test_error1_response);
    RUN_TEST(test_error1_response2);
    RUN_TEST(test_error1_response3);
    RUN_TEST(test_error2_response);
    RUN_TEST(test_error2_response2);
    RUN_TEST(test_error2_response3);
    RUN_TEST(test_zero_response);
    RUN_TEST(test_negativeValue_response);
    RUN_TEST(test_injectedLastValue_ifError1Response);
    RUN_TEST(test_injectedLastValue_ifError2Response);
    RUN_TEST(test_injectedLastValue_ifZeroResponse);
    RUN_TEST(test_zero_response2);
    RUN_TEST(test_negativeValue_response2);
    RUN_TEST(test_injectedLastValue_ifError1Response2);
    RUN_TEST(test_injectedLastValue_ifError2Response2);
    RUN_TEST(test_injectedLastValue_ifZeroResponse2);
    RUN_TEST(test_zero_response3);
    RUN_TEST(test_negativeValue_response3);
    RUN_TEST(test_injectedLastValue_ifError1Response3);
    RUN_TEST(test_injectedLastValue_ifError2Response3);
    RUN_TEST(test_injectedLastValue_ifZeroResponse3);
    //RUN_TEST(test_string_equal_ignore_case);
    //RUN_TEST(test_string_to_upper_case);
    //RUN_TEST(test_string_replace);

    UNITY_END(); // stop unit testing
    //USB_SERIAL.begin(115200);
    //sensor.initSensorCom();
    //sensorMocker.initMock();
    // expect no value
    //sensor.getCurrentDistance();
    // expect false value
    //sensorMocker.injectCustomResponse(Error1SensorResponse1);
    //sensor.getCurrentDistance();
    // excpect good value
    //sensorMocker.injectCustomResponse(GoodSensorResponse1);
    //sensor.getCurrentDistance();

}

void loop(){}