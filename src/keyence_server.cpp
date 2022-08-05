/**
 * @file keyence_server.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-08-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "keyence_server.h"

keyence_server::keyence_server(const char* ip, uint16_t port)
{
    std::cout << "creating keyence server with custom ip: " <<ip<< ", port: "<<port<< std::endl;
    IP = ip;
    PORT = port;
}
keyence_server::keyence_server()
{
    std::cout << "creating keyence server with default ip: " <<this->IP<< ", port: "<<this->PORT<< std::endl;

    ip_port_map["oscilloscop"]["192.168.0.105"]=3000;
    ip_port_map["delta"]["192.168.0.201"]=3344;
    ip_port_map["keyence"]["192.168.0.104"]=24687;
	}
keyence_server::~keyence_server()
{
    delete ServObject;
}

/********* server methods *********/
void keyence_server::server_connect()
{
	ServObject = new sockpp::tcp_acceptor(PORT);
	if (!ServObject) {
		std::cerr << "Error creating the server: " << ServObject->last_error_str() << std::endl;
		return;
	}
	std::cout << "Awaiting connections on port " << PORT << "..." << std::endl;

	while (true) {
		sockpp::inet_address peer;
		// Accept a new client connection
		sockpp::tcp_socket sock = ServObject->accept(&peer);
		std::cout << "Received a connection request from " << peer << std::endl;
		if (!sock) {
			std::cerr << "Error accepting incoming connection: " 
				<< ServObject->last_error_str() << std::endl;
		}
        // Read data from keyence
        ssize_t n = sock.read(&Request[0], DATA_LENGTH);
        std::cout << "n bytes: " << n << std::endl;
        std::cout << "data received: "<<Request.c_str() << std::endl;		
		sock.write(Request.c_str() , DATA_LENGTH);
		std::cout << "data sent: "<<Request.c_str() << std::endl;		

	}
}

void keyence_server::create_sensor ()
{
    KeyenceDistSensor= new IdistanceSensor (1, new keyence::keyenceWinSocket(this->keyence_controller_ip, this->keyence_controller_port)); // instance sensor
}
void keyence_server::init_sensor ()
{
    KeyenceDistSensor->initSensorCom(); // init sensor communication
}
double keyence_server::get_value ()
{
    return KeyenceDistSensor->getCurrentDistance(); // get sensor mesured data
}