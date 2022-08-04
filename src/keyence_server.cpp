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
		else {
			// Create a thread and transfer the new stream to it.
			//thread thr(run_echo, std::move(sock));
			//thr.detach();
		}
	}



}