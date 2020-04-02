#define HASH_SIZE_512
#include "headers/headers.hpp"
using json = nlohmann::json;
using namespace std;

void after_login(string &name, std::shared_ptr<jogador> jog, std::shared_ptr<server_client_socket> cliente) {
	jog->set_socket(cliente);
	int room_num = -1;
	string tosend = "Menu Choose an option:\n\t1- Enter room\n You selected (1)\n";
	cliente->sendtoclient(tosend);
	while(room_num < 0){
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
			room_num = -1;
	}
	//jog->set_server_client_socket(cliente);
	SALAS::enter_sala_jog(room_num, jog);
	while(!jog->sala_atual->get_has_ended()){
		this_thread::sleep_for(chrono::milliseconds(250));
	}
	persman::save(name);
}

bool token_login(std::shared_ptr<server_client_socket> cliente, std::string token){//not reference to client because is other thread
	bool returnv;
	//string nname, pass;
	int auth = 0/*, trys = 3*/;
	//while(trys--){
		/*cout << "Insert name : ";
		cout.flush();
		cin >> nname;
		cout << "Insert pass : ";
		cout.flush();
		cin >> pass;*/
		/*string iname = "Insert name : ", ipass = "Insert pass : ";
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
		ljogadores.load_if_not_create(nname, pass);*/
		auth = persman::load(token);
		if(!auth){
			string iname = "Insert new name: ", nname;
			cliente->sendtoclient(iname);
			//cliente->recvfromclient(10000);
			while (cliente->isempty()) {}
			nname = cliente->get();
			cliente->next();
			persman::new_jogador(token, nname);
		}
		after_login(token, persman::get(token), cliente);
		cout << "Loging out" << endl;
		returnv = 1;
	//}trys end
	cliente->disconect();
	return returnv;
}
/*
		string dn = "dummy", dps = "edu";
		dps = generate_hash(dps);
		ljogadores.new_jogador(dn, dps);
*/
int main(){
	cout<< __cplusplus << endl;
	SALAS::create_sala_bot(0);
	thread server_thread(server);
	//thread authsv_thread(auth_server);
	auth_server();
	//login();
	persman::save_all();
}