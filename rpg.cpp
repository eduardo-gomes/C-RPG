#include "headers/headers.hpp"
using json = nlohmann::json;
//using namespace std;

void after_login(std::string &name, std::shared_ptr<jogador> jog, std::shared_ptr<server_client_socket> cliente) {
	jog->connect(cliente);
	while(jog->is_connected()){
		menu::menu(jog);
		persman::save(name);
	}
}

void token_login(std::shared_ptr<server_client_socket> cliente, std::string token){//not reference to client because is other thread
	if (!persman::load(token)) {//handle nlohmann::detail::out_of_range
		persman::create_jogador(cliente);
	}
	after_login(token, persman::get(token), cliente);
	cout << "Loging out" << endl;
	//cliente->disconect();
}
/*
		string dn = "dummy", dps = "edu";
		dps = generate_hash(dps);
		ljogadores.new_jogador(dn, dps);
*/
void close_server(int){
	continue_running = 0;
	kill_server_socket();
	std::cout << " Saving all players" << std::endl;
	persman::save_all();
	signal(SIGINT, SIG_DFL);
	raise(SIGINT);
}
int main(){
	cout<< __cplusplus << endl;
	signal(SIGINT, close_server);
	thread server_thread(server);
	thread authsv_thread(auth_server);
	std::cout << "Press Ctrl+C to close" << std::endl;
	server_thread.join();
	//login();
}