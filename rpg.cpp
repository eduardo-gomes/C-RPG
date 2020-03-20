#define HASH_SIZE_512
#include "headers/headers.hpp"
#include "headers/sockets.hpp"
using json = nlohmann::json;
using namespace std;
data_jogadores ljogadores;
SALAS salas;

void after_login(string & name, jogador* jog){
	int room_num;
ENTER_NUM:
	string chose = "Enter room number (0000-9999): ", s_num;
	cliente->sendtoclient(chose);
	// cout << "Enter room number (0000-9999): ";
	// cout.flush();
	// cin >> room_num;
	//cliente->recvfromclient(0);
	while (cliente->isempty()) {}
	room_num = atoi(cliente->get().c_str());
	cliente->next();
	if(room_num > 9999 || room_num < 0)
		goto ENTER_NUM;
	salas.enter_sala(room_num, jog);
	ljogadores.save(name);
}

bool login(){
	bool returnv;
	string nname, pass;
	int auth = 0, trys = 3;
	while(trys--){
		/*cout << "Insert name : ";
		cout.flush();
		cin >> nname;
		cout << "Insert pass : ";
		cout.flush();
		cin >> pass;*/
		string iname = "Insert name : ", ipass = "Insert pass : ";
		cliente->sendtoclient(iname);
		//cliente->recvfromclient(10000);
		while(cliente->isempty()){}
		nname = cliente->get();
		cliente->next();
		cliente->sendtoclient(ipass);
		//cliente->recvfromclient(10000);
		while (cliente->isempty()) {
		}
		pass = cliente->get();
		cliente->next();
		pass = generate_hash(pass);
		ljogadores.load_if_not_create(nname, pass);
		auth = ljogadores.auth(nname, pass);
		cout << "auth: " << auth << endl;
		if(!auth)
			cout << "Invalid credentials" << endl;
		else{
			after_login(nname, ljogadores.get(nname));
			cout << "Loging out" << endl;
			returnv = 1;
			goto RET;
		}
	}
	cout << "Try again later" << endl;
	returnv = 0;
	RET:
	cliente->~server_client_socket();
	return returnv;
}
/*
		string dn = "dummy", dps = "edu";
		dps = generate_hash(dps);
		ljogadores.new_jogador(dn, dps);
*/
int main(){
	cout<< __cplusplus << endl;
	salas.create_sala_bot(0);
	//thread server_thread(server);
	server();
	//login();
	ljogadores.save_all();
}