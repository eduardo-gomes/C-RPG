#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>
//#include <nlohmann/json.hpp>
#include "sockets.hpp"
//using json = nlohmann::json;

int sock, valread;
char buffer[1025] = {0};
void recieved() {
}
void handle_recived(){
	
}
int main() {
	endereco = "127.0.0.1";
	sock = confsocket();
	std::thread recvthread;
	if (sock > 0) {
		std::cout << "Connected" << std::endl;
		recvthread = std::thread(clientsocket::recvloop);
	}
	while (clientsocket::connected) {
		if (!clientsocket::isempty()) {
			std::cout << clientsocket::get() << std::endl;
			clientsocket::next();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	recvthread.join();
	return 0;
}