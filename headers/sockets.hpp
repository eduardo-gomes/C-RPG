#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <csignal>
#include <string>
#define PORT 8080
#define LOGINPORT 1406
#ifndef LINK
#define LINK "http://localhost:8081"
#endif

#include <chrono>
#include <thread>
class server_client_socket;
void token_login(std::shared_ptr<server_client_socket>, std::string);
class jogador;
class server_client_socket {
	private:
	bool hasdisconected;
	bool auth;
	std::string auth_name;
	static const char msg_break = '\n';
	static const unsigned int buffer_size = 1024;
	char buffer[buffer_size+1];
	std::thread proc;
	std::shared_ptr<jogador> socket_of_jogador;
	public:
	std::deque<std::string> messages;
	std::string readed;
	long unsigned int readedindex = 0;
	int socket_id;
	std::shared_ptr<jogador>& get_jogador(){return socket_of_jogador;}
	void set_jogador(std::shared_ptr<jogador>& newjog){socket_of_jogador = newjog;}
	server_client_socket(){
		buffer[buffer_size] = '\0';
		hasdisconected = 0;
	}
	virtual ssize_t sendtoclient(const std::string &str) {
		std::cout << "Socket Out: " << str << std::endl;
		return send(socket_id, &str[0], str.length(), 0);
	}
	int next(){
		if(messages.empty()) return -1;
		messages.pop_front();
		return 0;
	}
	bool isempty(){
		return messages.empty();
	}
	std::string &get(){
		return messages.front();
	}
	void clear_msg(){
		messages.clear();
	}
	const std::string& get_token(){
		return auth_name;
	}
	long int recvfromclient() {
		long int val;
		//memset(buffer, -1, 1024);
		val = read(socket_id, buffer, 1024);
		if (val == -1) {
			if(errno == EAGAIN) return 0;
			if(errno == ECONNRESET) return -2;
			perror("socket error");
			return -1;
		} else {
			/* readedindex = 0;
			readed.clear(); */
			buffer[val] = '\0';//packet end
			long unsigned int msg_sz;
			char *find = strchr(buffer, msg_break);
			char* next = buffer;
			while (find <= &buffer[val] && find != NULL){
				msg_sz = (unsigned long)(find - next);
				//if (readed.capacity() < readedindex + msg_sz) readed.reserve(readedindex + msg_sz + 100);
				//memcpy(&readed[readedindex], next, msg_sz);
				readed.append(next, msg_sz);
				readedindex += (long unsigned)val;
				messages.push_back(readed);
				readedindex = 0;
				readed.clear();
				//if (readed.capacity() < readedindex + msg_sz) readed.reserve(readedindex + msg_sz + 100);
				next = find +1;
				find = strchr(next, msg_break);
				msg_sz = (unsigned long)(find - next);
				if(find == NULL){
					msg_sz = strlen(next);
				}
				//memcpy(&readed[readedindex], next, msg_sz);
				readed.append(next, msg_sz);
				readedindex += msg_sz;
			}
			if (!(find <= &buffer[val])) {
				msg_sz = (long unsigned)val;
				//if(readed.capacity() < readedindex + msg_sz)readed.reserve(readedindex + msg_sz + 100);
				//memcpy(&readed[readedindex], buffer, msg_sz);
				readed.append(next, msg_sz);
				readedindex += msg_sz;
			}
		}
		return val;
	}
	virtual int disconect(){
		if (hasdisconected) return 0;
		char eofc = 0x1c;
		send(socket_id, &eofc, 1, 0);
		hasdisconected = 1;
		return shutdown(socket_id, SHUT_RDWR);
	}
	void auth_login(std::string &authst, std::shared_ptr<server_client_socket> ptr) {
		auth = 1;
		auth_name = authst;
		proc = std::thread(token_login, ptr, authst);
	}
	server_client_socket(int socket): server_client_socket() {
		auth = 0;
		socket_id = socket;
		int iMode = 1;
		ioctl(socket_id, FIONBIO, &iMode);  //non-blocking
		//proc = std::thread(login, this);
	}
	virtual ~server_client_socket(){
		//proc.~thread();
		std::string goodbye = "Closing connection";
		sendtoclient(goodbye);
		close(socket_id);
	}
};
class server_client_null: public server_client_socket{
	ssize_t sendtoclient(std::string &){return 0;}
	int disconect(){return 0;}
	//recv
};
server_client_null NULL_CLIENT_NULL;
std::shared_ptr<server_client_socket> NULL_CLIENT ((server_client_socket *)(&NULL_CLIENT_NULL));
std::map<int, std::shared_ptr<server_client_socket>> clientes;
std::mutex clientes_mtx;

void recv_loop(){
	while(continue_running){
		std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + std::chrono::milliseconds(5);
		clientes_mtx.lock();
		for (std::map<int, std::shared_ptr<server_client_socket>>::iterator it = clientes.begin(); it != clientes.end(); ++it) {
			if((it->second)->recvfromclient() == -2){
				it->second->~server_client_socket();
				it = clientes.erase(it);
				if(it == clientes.end()) break;
				if(it != clientes.begin()) --it;//no problem if it jump the new first
			}
		}
		clientes_mtx.unlock();
		std::this_thread::sleep_until(tp);
	}
}

std::deque<server_client_socket *> waiting_auth;
std::mutex waiting_auth_mtx;
void try_auth(server_client_socket *auth){
	if(!auth->isempty()){
		std::string auth_msg = auth->get();
		auth->next();
		using json = nlohmann::json;
		json j;
		try{
		j = nlohmann::json::parse(auth_msg);
		}
		catch(const nlohmann::detail::parse_error &){
			goto CLOSE;
		}
		if(j.is_object()){
			int sid = atoi(j["socket"].get<std::string>().c_str());
			std::string token = j["token"].get<std::string>();
			clientes_mtx.lock();
			auto iter = clientes.find(sid);
			if(iter != clientes.end()){
				iter->second->auth_login(token, iter->second);
			}else std::cout << "Recived invalid sid" << std::endl;
			clientes_mtx.unlock();
		}else std::cout << "Recived invalid auth_json" << std::endl;
	}
	CLOSE:
	auth->disconect();
}
void auth_loop(){
	int ret;
	while (continue_running) {
		std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + std::chrono::milliseconds(20);
		waiting_auth_mtx.lock();
		for (std::deque<server_client_socket *>::iterator it = waiting_auth.begin(); it != waiting_auth.end(); ++it) {
			ret = (*it)->recvfromclient();
			if(ret > 0){
				try_auth(*it);
			}else if (ret == -2) {
				(*it)->~server_client_socket();
				it = waiting_auth.erase(it);
				if (it == waiting_auth.end()) break;
				if (it != waiting_auth.begin()) --it;  //no problem if it jump the new first
			}
		}
		waiting_auth_mtx.unlock();
		std::this_thread::sleep_until(tp);
	}
}
void new_connection(int socket_id){
	std::shared_ptr<server_client_socket> novo (new server_client_socket(socket_id));
	std::string tosend = "To login open:\n" LINK "/jogo/auth/handler?sid=";
	tosend += std::to_string(socket_id);
	tosend += '\n';
	novo->sendtoclient(tosend);
	clientes_mtx.lock();
	clientes.insert(std::make_pair(socket_id, novo));
	clientes_mtx.unlock();
}

int server_fd_server;
void server() {
	signal(SIGPIPE, SIG_IGN);
	int new_socket, valread = 0;
	server_fd_server = 0;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	std::string hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd_server = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd_server, (struct sockaddr *)&address,
			 sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd_server, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	std::thread(recv_loop).detach();
	while ((new_socket = accept(server_fd_server, (struct sockaddr *)&address, (socklen_t *)&addrlen)) > 0){
		new_connection(new_socket);
		//std::thread(login).detach();
	}
	perror("accept");
	exit(EXIT_FAILURE);

	//valread = read(new_socket, buffer, 1024);
	printf("%s\n", buffer);
	send(new_socket, hello.c_str(), hello.length(), 0);
	printf("Hello message sent %d\n", valread);
	return;
}
int server_fd_auth;
void auth_server() {
	int new_socket, valread = 0;
	server_fd_auth = 0;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	std::string hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd_auth = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd_auth, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(LOGINPORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd_auth, (struct sockaddr *)&address,
			 sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd_auth, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	std::thread(auth_loop).detach();
	while ((new_socket = accept(server_fd_auth, (struct sockaddr *)&address, (socklen_t *)&addrlen)) > 0) {
		waiting_auth_mtx.lock();
		waiting_auth.push_back(new server_client_socket(new_socket));
		waiting_auth_mtx.unlock();
		//std::thread(login).detach();
	}
	perror("accept");
	exit(EXIT_FAILURE);

	//valread = read(new_socket, buffer, 1024);
	printf("%s\n", buffer);
	send(new_socket, hello.c_str(), hello.length(), 0);
	printf("Hello message sent %d\n", valread);
	return;
}
void kill_server_socket(){
	close(server_fd_auth);
	close(server_fd_server);
}