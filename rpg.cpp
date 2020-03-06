#include "headers/headers.hpp"
using json = nlohmann::json;
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
	string nname = "edu";
	cout << "Insert name : ";
	cout.flush();
	cin >> nname;
	new_jogador(nname);
	string sn = "sala1";
	sala sala1(sn);
	sala1.add_personagem(ljogadores[nname]);
	/*for(int i = 0; i < 11; ++i){//////////////////////////////////weapon material upgrade
		cout << ljogadores[nname]->get_arma(0)->material_upgrade_cost() << " arma 0 material upgrade cost " << *ljogadores[nname]->get_arma(0)->get_material_name() << endl;
		ljogadores[nname]->get_arma(0)->add_xp(ljogadores[nname]->get_arma(0)->material_upgrade_cost());
		ljogadores[nname]->get_arma(0)->material_upgrade();
	}
	for(int i = 0; i < 10; ++i){//////////////////////////////////player level upgrade
		cout << "lv atual : " << ljogadores[nname]->get_level() << "		" << ljogadores[nname]->xp_to_next_level() << " xp to next level		all xp: " << ljogadores[nname]->get_all_xp() << endl;
		//ljogadores[nname]->try_level_up();
		ljogadores[nname]->add_xp(ljogadores[nname]->xp_to_next_level());
	}
	//////////////////////////////////jogador to json to jogador
	json j = *(ljogadores[nname]), jjog;
	jogador jog;
	from_json(j, jog);
	jjog = jog;
	cout << nname << " " << j << endl << "jog " << jjog << endl;*/
	inimigo inimi1;
	sala1.add_personagem(&inimi1);
	//for (int i = 0; i < 3; ++i) //////////////////////////////////round sumulation
		sala1.round_loop();

	cout << "All players:" << endl;
	for(auto i : ljogadores){
		json j = (jogador *)i.second;
		cout << i.first << " = " << j << endl;
	}
}