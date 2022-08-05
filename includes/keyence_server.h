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

class keyence_server
{
private:
    private:
    sockpp::socket_initializer sockInit;
    sockpp::tcp_acceptor* ServObject;
    const char* IP="127.0.0.1";
    uint16_t PORT=6555;
    const int DATA_LENGTH =1024;
    char Response[1024]={};
    std::string Request;
    int incomingData=0;
    std::map<std::string, std::map<std::string, uint16_t> > ip_port_map;

    const char* keyence_controller_ip = "192.168.0.104"; //ip controller
    uint16_t keyence_controller_port = 24687; // port
    IdistanceSensor* KeyenceDistSensor;
public:
    keyence_server();
    keyence_server(const char* ip, uint16_t port);
    ~keyence_server();

    /**** server methods ***/
    void server_connect();
    void server_parse();
    void create_sensor();
    void init_sensor();
    void send_cmd();
    double get_value();
};


