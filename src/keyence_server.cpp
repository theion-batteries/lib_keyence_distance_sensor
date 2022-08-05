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
	std::cout << "creating keyence server with custom ip: " << ip << ", port: " << port << std::endl;
	IP = ip;
	PORT = port;
}
keyence_server::keyence_server()
{
	std::cout << "creating keyence server with default ip: " << this->IP << ", port: " << this->PORT << std::endl;
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
		std::cout << "data received: " << Request.c_str() << std::endl;
		std::string dataAsStr = Request.c_str();
		server_parse(dataAsStr);
		sock.write(Request.c_str(), DATA_LENGTH);
		std::cout << "data sent: " << Request.c_str() << std::endl;

	}
}

void keyence_server::create_sensor1()
{
	std::cout << "request received, creating sensor interface 1 " << std::endl;

	KeyenceDistSensorHEAD1 = new IdistanceSensor(1, new keyence::keyenceWinSocket(this->keyence_controller_ip, this->keyence_controller_port)); // instance sensor
}
void keyence_server::create_sensor2()
{
	std::cout << "request received, creating sensor interface 2 " << std::endl;

	KeyenceDistSensorHEAD2 = new IdistanceSensor(2, new keyence::keyenceWinSocket(this->keyence_controller_ip, this->keyence_controller_port)); // instance sensor
}
void keyence_server::create_sensor3()
{
	std::cout << "request received, creating sensor interface 3 " << std::endl;

	KeyenceDistSensorHEAD3 = new IdistanceSensor(3, new keyence::keyenceWinSocket(this->keyence_controller_ip, this->keyence_controller_port)); // instance sensor
}
void keyence_server::init_sensor_controller()
{
	create_sensor1();
	create_sensor2();
	create_sensor3();
	std::cout << "request received, asking controller for settings " << std::endl;

	KeyenceDistSensorHEAD1->initSensorCom(); // init sensor communication
}
void keyence_server::get_value_output1()
{
	std::cout << "request received, asking controller for value head 1 " << std::endl;

	LastValueHead1 = KeyenceDistSensorHEAD1->getCurrentDistance(); // get senssor mesured data
}
void keyence_server::get_value_output2()
{
	std::cout << "request received, asking controller for value head 2 " << std::endl;

	LastValueHead2 = KeyenceDistSensorHEAD2->getCurrentDistance(); // get senssor mesured data
}
void keyence_server::get_value_output3()
{
	std::cout << "request received, asking controller for value head 3 " << std::endl;

	LastValueHead3 = KeyenceDistSensorHEAD3->getCurrentDistance(); // get senssor mesured data
}
void keyence_server::get_value_outputAll()
{
	std::cout << "request received, asking controller for values all heads " << std::endl;

	lastValuesAll = KeyenceDistSensorHEAD1->getValuesAll();
}
void keyence_server::server_parse(std::string& msg)
{

	std::cout << "parsing request: " << msg << std::endl;
	std::cout << "searching callback function  " << std::endl;
	auto iter = keyence_callbacks.find(msg);
    if(iter == keyence_callbacks.end()) { std::cout <<"not found"; }
	init_sensor_controller();
	iter->second;
	//get1_call;

}
