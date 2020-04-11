#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

#include <deque>
#include <iostream>
#include <string>
#define PORT 8080
std::string endereco;
extern int sock;

namespace clientsocket {
char buffer[1025];
std::deque<std::string> messages;
std::string readed;
bool connected = 0;
long unsigned readedindex;
const char msg_break = '\003';
long int recvfromclient() {
	long int val;
	//memset(buffer, -1, 1024);
	val = read(sock, buffer, 1024);
	if (val == -1) {
		if (errno == EAGAIN) return 0;
		if (errno == ECONNRESET) return -2;
		perror("socket error");
		return -1;
	} else {
		buffer[val] = '\0';	 //packet end
		long unsigned int msg_sz;
		char *find = strchr(buffer, msg_break);
		char *next = buffer;
		while (find <= &buffer[val] && find != NULL) {
			msg_sz = (unsigned long)(find - next);
			readed.append(next, msg_sz);
			readedindex += (long unsigned)val;
			messages.push_back(readed);
			readedindex = 0;
			readed.clear();
			next = find + 1;
			find = strchr(next, msg_break);
			msg_sz = (unsigned long)(find - next);
			if (find == NULL) {
				msg_sz = strlen(next);
			}
			/*readed.append(next, msg_sz);
			find = strchr(next, msg_break);
			readedindex += msg_sz;*/
		}
		if (!(find <= &(buffer[val]))) {
			msg_sz = (long unsigned)val;
			readed.append(next, msg_sz);
			readedindex += msg_sz;
		}
	}
	return val;
}
bool isempty(){
	return messages.empty();
}
void next(){
	messages.pop_front();
}
std::string &get(){
	return messages.front();
}
void recvloop(){
	long ret;
	while(1){
		ret = recvfromclient();
		if(ret == 0){
			std::this_thread::sleep_for(std::chrono::nanoseconds(300));
		}else if (ret < 0){
			std::cout << "Error recvloop errno: " << errno << std::endl;
			connected = 0;
			return;
		}
	}
}
}  // namespace socket

/*int tryread(int sock) {
	int valread;
	valread = recv(sock, buffer, 1024, 0);
	if (valread > 0) {
		buffer[valread] = 0;
	} else if (errno != EWOULDBLOCK) {
		abort();
	}
	return valread;
}*/

int confsocket() {
	struct sockaddr_in serv_addr;
	std::string hello = "Hello from client";
	//char buffer[1025] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0) {
		std::cout << "Socket creation error" << std::endl;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, endereco.c_str(), &serv_addr.sin_addr) <= 0) {
		std::cout << "Invalid address/ Address not supported" << std::endl;
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		if (errno != EINPROGRESS) {
			std::cout << "Connection Failed " << errno << std::endl;
			return -1;
		} else {
			int result;
			socklen_t result_len = sizeof(result);
			if (getsockopt(sock, SOL_SOCKET, SO_ERROR, &result, &result_len) < 0) {
				std::cout << "Connection Failed after EINPROGRESS " << errno << std::endl;
				return -1;
			}
		}
		clientsocket::connected = 1;
	}
	return sock;
}
