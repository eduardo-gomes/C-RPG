#include "headers/headers.hpp"
using namespace std;
map<string, jogador *> ljogadores;

void new_jogador(string name){
	if(ljogadores.find(name) != ljogadores.end()){
		cout << "jogador " << name << " já existe" << endl;
		return;
	}
	ljogadores[name] = new jogador(name);
}

int main(){
	cout<< __cplusplus << endl;
	cout << "Insert name : ";
	cout.flush();
	string nname;
	cin >> nname;
	new_jogador(nname);
	string sn = "sala1";
	sala sala1(sn);
	sala1.add_personagem(ljogadores[nname]);
	for(int i = 0; i < 5; ++i)
		sala1.round_loop();
}