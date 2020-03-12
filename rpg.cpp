#define HASH_SIZE_512
#include "headers/headers.hpp"
using json = nlohmann::json;
using namespace std;
data_jogadores ljogadores;
SALAS salas;

void after_login(string & name, jogador* jog){
	int room_num;
ENTER_NUM:
	cout << "Enter room number (0000-9999): ";
	cout.flush();
	cin >> room_num;
	if(room_num > 9999 || room_num < 0)
		goto ENTER_NUM;
	salas.enter_sala(room_num, jog);
	ljogadores.save(name);
}

bool login(){
	string nname, pass;
	int auth = 0, trys = 3;
	while(trys--){
		cout << "Insert name : ";
		cout.flush();
		cin >> nname;
		cout << "Insert pass : ";
		cout.flush();
		cin >> pass;
		pass = generate_hash(pass);
		ljogadores.load_if_not_create(nname, pass);
		auth = ljogadores.auth(nname, pass);
		cout << "auth: " << auth << endl;
		if(!auth)
			cout << "Invalid credentials" << endl;
		else{
			after_login(nname, ljogadores.get(nname));
			cout << "Loging out" << endl;
			return 1;
		}
	}
	cout << "Try again later" << endl;
	return 0;
}
/*
		string dn = "dummy", dps = "edu";
		dps = generate_hash(dps);
		ljogadores.new_jogador(dn, dps);
*/
int main(){
	cout<< __cplusplus << endl;
	salas.create_sala_bot(0);
	login();
	ljogadores.save_all();
}