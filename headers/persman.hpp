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
string hash_to_char(string &hash);
bool comp_hash(string &a, string &b);

class data_jogadores{
	public:
		map<string, pair<jogador *, string>> lista;
		void load_if_not_create(string &name, string new_hash) {
			if(!load(name)){
				new_jogador(name, new_hash);
			}
		}
		bool auth(string& name, string &new_hash){
			std::map<string, pair<jogador *, string>>::iterator it = lista.find(name);
			if(it == lista.end()){
				if(load(name)){
					it = lista.find(name);
					if(it == lista.end())
						throw NotFindAfterLoad();
				}
			}
			return comp_hash(it->second.second, new_hash);
		}
		bool load(string& name){
			bool status = 1;
			std::map<string, pair<jogador *, string>>::iterator it = lista.find(name);
			if (it == lista.end()){
				fstream jogador_file, pass_file;
				string fname = "jogadores/";
				fname += name;
				string fpass = fname;
				fname += ".json";
				fpass += ".sha";
				jogador_file.open(fname, ifstream::in);
				pass_file.open(fpass, ifstream::in | ios::binary);
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
				#ifdef HASH_SIZE_512
					#define HASH_SIZE 512/8
				#else
					#define HASH_SIZE 256/8
				#endif
				string pass;
				pass.resize(HASH_SIZE);
				if(!pass_file.read(&pass[0], HASH_SIZE)){
					//cout << "read hash: " << hash_to_char(pass) << endl;
					status = 0;
				}
				if(status) lista[name] = make_pair(jog, pass);
				jogador_file.close();
				pass_file.close();
			}
			return status;
		}
		jogador *get(string &name){
			std::map<string, pair<jogador *, string>>::iterator it = lista.find(name);
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
			return it->second.first;
		}
		jogador* new_jogador(string& name, string& hash){
			if(lista.find(name) != lista.end()){
				cout << "jogador " << name << " já existe" << endl;
				return lista[name].first;
			}
			fstream pass_file;
			string fpass = "jogadores/";
			fpass += name;
			fpass += ".sha";
			pass_file.open(fpass, ifstream::out | ifstream::trunc | ios::binary);
			pass_file.write(&hash[0], (std::streamsize)hash.size());
			pass_file.close();
			lista[name].first = new jogador(name);
			lista[name].second = hash;
			return lista[name].first;
		}
		void save(string &name){
			std::map<string, pair<jogador *, string>>::iterator it = lista.find(name);
			if(it != lista.end()){
				fstream jogador_file;
				string fname = "jogadores/" ;
				fname += name;
				fname += ".json";
				jogador_file.open(fname, ifstream::out | ifstream::trunc);
				if (jogador_file.good()){
					nlohmann::json jout;
					to_json(jout, it->second.first);
					jogador_file << jout;
					jogador_file.close();
				}
			}
		}
		void save_all(){
			for (std::map<string, pair<jogador *, string>>::iterator it = lista.begin(); it != lista.end(); ++it){
				fstream jogador_file;
				string fname = "jogadores/";
				fname += it->first;
				fname += ".json";
				jogador_file.open(fname, ifstream::out | ifstream::trunc);
				if(jogador_file.good()){
					nlohmann::json jout;
					to_json(jout, it->second.first);
					jogador_file << jout;
					jogador_file.close();
				}
			}
		}
};

bool comp_hash(string &a, string &b){
	return a.compare(b) == 0;
}
string generate_hash(string &msg);
string hash_to_char(string &hash){
	#ifdef HASH_SIZE_512
		#ifndef HASH_SIZE_256
		#define HASH_SIZE_256
		#endif
		#define HASH_SIZE 512/8
	#else
		#define HASH_SIZE 256/8
	#endif
	string out;
	char tochar[2];
	for(long unsigned int x = 0; x < HASH_SIZE; ++x){//-Werror=sign-conversion
		tochar[0] = hash[x] >> 4 & 0xF;
		tochar[1] = hash[x] & 0xF;
		if(tochar[0] > 9)
			tochar[0] += 'A'-10;
		else
			tochar[0] += '0';
		if (tochar[1] > 9)
			tochar[1] += 'A'-10;
		else
			tochar[1] += '0';
		out += tochar[0];
		out += tochar[1];
	}
	#undef HASH_SIZE
	return out;
}
#include "./sha256.hpp"