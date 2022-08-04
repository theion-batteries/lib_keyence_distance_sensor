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
    int incomingData=0;
public:
    keyence_server();
    keyence_server(const char* ip, uint16_t port);
    ~keyence_server();

    /**** server methods ***/
    void server_connect();
};


