/**
 * @file keyence_server.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-08-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "sockpp/socket.h"
#include <iostream>
#include <string>
#include "sockpp/tcp_acceptor.h"
#include <stdlib.h>
#include "distance_sensor_interface.h"
#include <functional>
class keyence_server
{
private:
private:
    sockpp::socket_initializer sockInit;
    sockpp::tcp_acceptor* ServObject;
    const char* IP = "127.0.0.1";
    uint16_t PORT = 6555;
    const int DATA_LENGTH = 1024;
    char Response[1024] = {};
    std::string Request;
    int incomingData = 0;
    std::map<std::string, std::pair<std::string, uint16_t> > ip_port_map =
    {
        {"oscilloscop",{"192.168.0.105",3000}},
        {"delta",{"192.168.0.201",3344}},
        {"keyence",{"192.168.0.104",24687}},
    };
    using fnCmd = std::function<void(keyence_server*)>;
    std::map < std::string, fnCmd > keyence_callbacks = 
    {
        std::make_pair("set_R0", std::mem_fn(&keyence_server::init_sensor_controller)),
        std::make_pair("set_Q0", std::mem_fn(&keyence_server::init_sensor_controller)),
        std::make_pair("get1", std::mem_fn(&keyence_server::get_value_output1)),
        std::make_pair("get2", std::mem_fn(&keyence_server::get_value_output2)),
        std::make_pair("get3", std::mem_fn(&keyence_server::get_value_output3)),
        std::make_pair("get_all", std::mem_fn(&keyence_server::get_value_outputAll))
          };

    /* std::map<std::string, void (keyence_server::*)()> keyence_callbacks = {
         {"get1",&keyence_server::get_value_output1}, {"get2",&keyence_server::get_value_output2},
         {"get3",&keyence_server::get_value_output3}, {"get_all",&keyence_server::get_value_outputAll},
         {"set_R0",&keyence_server::init_sensor_controller}, {"set_Q0",&keyence_server::init_sensor_controller}
     };*/
    const char* keyence_controller_ip = "192.168.0.104"; //ip controller
    uint16_t keyence_controller_port = 24687; // port
    IdistanceSensor* KeyenceDistSensorHEAD1;
    IdistanceSensor* KeyenceDistSensorHEAD2;
    IdistanceSensor* KeyenceDistSensorHEAD3;

    double LastValueHead1 = 100.0;
    double LastValueHead2 = 0;
    double LastValueHead3 = 0;
    std::vector<double> lastValuesAll;
public:
    keyence_server();
    keyence_server(const char* ip, uint16_t port);
    ~keyence_server();

    /**** server methods ***/
    void server_connect();
    void server_parse(std::string& msg);
    void create_sensor1();
    void create_sensor2();
    void create_sensor3();

    void init_sensor_controller();
    void send_cmd();
    void get_value_output1();
    void get_value_output2();
    void get_value_output3();
    void get_value_outputAll();
};


