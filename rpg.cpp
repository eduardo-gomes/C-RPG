#include "headers/headers.hpp"
using json = nlohmann::json;
using namespace std;
class data_jogadores{
	public:
		map<string, jogador *> lista;
		jogador* get(string& name){
			std::map<string, jogador *>::iterator it = lista.find(name);
			if (it == lista.end()){
				fstream abrir;
				string fname = "jogadores/";
				fname += name;
				fname += ".json";
				abrir.open(fname, ifstream::in);
				if(abrir.good()){
					/*std::string content((std::istreambuf_iterator<char>(abrir)),
										(std::istreambuf_iterator<char>()));*/
					jogador* jog = new jogador();
					json readjog;
					abrir >> readjog;
					from_json(readjog, jog);
					jog->heal();
					return lista[name] = jog;
				}else{
					abrir.close();
					return new_jogador(name);
				}
			}else{
				return it->second;
			}
		}
		jogador* new_jogador(string& name){
			if(lista.find(name) != lista.end()){
				cout << "jogador " << name << " já existe" << endl;
				return lista[name];
			}
			return lista[name] = new jogador(name);
		}
		void save(string &name){
			std::map<string, jogador *>::iterator it = lista.find(name);
				if(it == lista.end()){
				fstream abrir;
				string fname = "jogadores/" ;
				fname += name;
				fname += ".json";
				abrir.open(fname, ifstream::out | ifstream::trunc);
				if (abrir.good()){
					json jout;
					to_json(jout, it->second);
					abrir << jout;
					abrir.close();
				}
			}
		}
		void save_all(){
			for (std::map<string, jogador *>::iterator it = lista.begin(); it != lista.end(); ++it){
				fstream abrir;
				string fname = "jogadores/";
				fname += it->first;
				fname += ".json";
				abrir.open(fname, ifstream::out | ifstream::trunc);
				if(abrir.good()){
					json jout;
					to_json(jout, it->second);
					abrir << jout;
					abrir.close();
				}
			}
		}
};
data_jogadores ljogadores;


int main(){
	cout<< __cplusplus << endl;
	string nname = "edu";
	cout << "Insert name : ";
	cout.flush();
	cin >> nname;
	//ljogadores.new_jogador(nname);
	string sn = "sala1";
	sala sala1(sn);
	sala1.add_personagem(ljogadores.get(nname));
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

	//cout << "All players:" << endl;
	/*for(auto i : ljogadores){
		json j = (jogador *)i.second;
		cout << i.first << " = " << j << endl;
	}*/
	//json j(ljogadores);
	//cout << j << endl;
	ljogadores.save_all();
}