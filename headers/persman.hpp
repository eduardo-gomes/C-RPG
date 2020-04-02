#pragma once
#include "headers.hpp"
/*
Conecta -> auth -> cria/carrega personagem -> main menu -> sala solo/multp -> loja

HERE:
Conecta -> auth -> cria/carrega personagem

todo next:
hash, store and compare
maybe salt
*/
using namespace std;
struct NotFindAfterLoad : public std::exception{
	const char * what () const throw (){
		return "Cant Find after load";
	}
};
//string hash_to_char(string &hash);
//bool comp_hash(string &a, string &b);

class data_jogadores{
	public:
		map<string, jogador *> lista;
		/*void load_if_not_create(string &name) {
			if(!load(name)){
				new_jogador(name);
			}
		}*/
		/*bool auth(string& name){
			std::map<string, jogador *>::iterator it = lista.find(name);
			if(it == lista.end()){
				if(load(name)){
					it = lista.find(name);
					if(it == lista.end())
						throw NotFindAfterLoad();
				}
			}
			return 1;
		}*/
		bool load(string& name){
			bool status = 1;
			std::map<string, jogador *>::iterator it = lista.find(name);
			if (it == lista.end()){
				fstream jogador_file;
				string fname = "jogadores/";
				fname += name;
				fname += ".json";
				jogador_file.open(fname, ifstream::in);
				jogador* jog = new jogador();
				if(jogador_file.good()){
					/*std::string content((std::istreambuf_iterator<char>(jogador_file)),
										(std::istreambuf_iterator<char>()));*/
					nlohmann::json readjog;
					jogador_file >> readjog;
					from_json(readjog, jog);
					jog->heal();
				}else
					status = 0;
				if(status) lista[name] = jog;
				jogador_file.close();
			}
			return status;
		}
		jogador *get(string &name){
			std::map<string, jogador *>::iterator it = lista.find(name);
			if (it == lista.end()){
				bool isloaded = load(name);
				if(!isloaded){
					isloaded = load(name);
				}
				if(isloaded){
					it = lista.find(name);
					if(it == lista.end()){
						throw NotFindAfterLoad();
					}
				}
			}
			return it->second;
		}
		jogador* new_jogador(string& name, string& jogador_name){
			if(this->load(name)){
				if(lista.find(name) != lista.end()){
					cout << "jogador " << name << " já existe" << endl;
					//to rename here
					return lista[name];
				}
			}
			lista[name] = new jogador(jogador_name);
			return lista[name];
		}
		void save(string &name){
			std::map<string, jogador *>::iterator it = lista.find(name);
			if(it != lista.end()){
				fstream jogador_file;
				string fname = "jogadores/" ;
				fname += name;
				fname += ".json";
				jogador_file.open(fname, ifstream::out | ifstream::trunc);
				if (jogador_file.good()){
					nlohmann::json jout;
					to_json(jout, it->second);
					jogador_file << jout;
					jogador_file.close();
				}
			}
		}
		void save_all(){
			for (std::map<string, jogador *>::iterator it = lista.begin(); it != lista.end(); ++it){
				fstream jogador_file;
				string fname = "jogadores/";
				fname += it->first;
				fname += ".json";
				jogador_file.open(fname, ifstream::out | ifstream::trunc);
				if(jogador_file.good()){
					nlohmann::json jout;
					to_json(jout, it->second);
					jogador_file << jout;
					jogador_file.close();
				}
			}
		}
};
