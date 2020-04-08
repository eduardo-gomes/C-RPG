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
namespace CPP_RPG::Server {
struct NotFindAfterLoad : public std::exception {
	const char *what() const throw() {
		return "Cant Find after load";
	}
};
//string hash_to_char(string &hash);
//bool comp_hash(string &a, string &b);
namespace menu {
	void weapon_chooser(std::shared_ptr<jogador> &jog);
}
namespace persman {
	std::map<string, std::shared_ptr<jogador>> lista;
	bool load(const string &name) {
		bool status = 1;
		std::map<string, std::shared_ptr<jogador>>::iterator it = lista.find(name);
		if (it == lista.end()) {
			fstream jogador_file;
			string fname = "jogadores/";
			fname += name;
			fname += ".json";
			jogador_file.open(fname, ifstream::in);
			std::shared_ptr<jogador> jog(new jogador());
			if (jogador_file.good()) {
				/*std::string content((std::istreambuf_iterator<char>(jogador_file)),
										(std::istreambuf_iterator<char>()));*/
				nlohmann::json readjog;
				jogador_file >> readjog;
				from_json(readjog, jog.get());
				jog->heal();
			} else
				status = 0;
			if (status) lista[name] = jog;
			jogador_file.close();
		}
		return status;
	}
	std::shared_ptr<jogador> &get(string &name) {
		std::map<string, std::shared_ptr<jogador>>::iterator it = lista.find(name);
		if (it == lista.end()) {
			bool isloaded = load(name);
			if (!isloaded) {
				isloaded = load(name);
			}
			if (isloaded) {
				it = lista.find(name);
				if (it == lista.end()) {
					throw NotFindAfterLoad();
				}
			}
		}
		return it->second;
	}
	std::shared_ptr<jogador> &new_jogador(const string &name, string &jogador_name) {
		if (load(name)) {
			if (lista.find(name) != lista.end()) {
				cout << "jogador " << name << " já existe" << endl;
				//to rename here
				return lista[name];
			}
		}
		lista[name] = std::shared_ptr<jogador>(new jogador(jogador_name));
		return lista[name];
	}
	void save(string &name) {
		std::map<string, std::shared_ptr<jogador>>::iterator it = lista.find(name);
		if (it != lista.end()) {
			fstream jogador_file;
			string fname = "jogadores/";
			fname += name;
			fname += ".json";
			jogador_file.open(fname, ifstream::out | ifstream::trunc);
			if (jogador_file.good()) {
				nlohmann::json jout;
				to_json(jout, it->second.get());
				jogador_file << jout;
				jogador_file.close();
			}
		}
	}
	void save_all() {
		for (std::map<string, std::shared_ptr<jogador>>::iterator it = lista.begin(); it != lista.end(); ++it) {
			fstream jogador_file;
			string fname = "jogadores/";
			fname += it->first;
			fname += ".json";
			jogador_file.open(fname, ifstream::out | ifstream::trunc);
			if (jogador_file.good()) {
				nlohmann::json jout;
				to_json(jout, it->second.get());
				jogador_file << jout;
				jogador_file.close();
			}
		}
	}
	std::shared_ptr<jogador> &create_jogador(std::shared_ptr<server_client_socket> &cliente) {
		string iname = "Insert new player name: ", nname;
		//cliente->clear_msg();
		cliente->sendtoclient(iname);
		while (cliente->isempty()) {
			ISEMPTY_DELAY
		}
		nname = cliente->get();
		cliente->next();
		std::shared_ptr<jogador> &newjog = new_jogador(cliente->get_token(), nname);
		newjog->connect(cliente);
		menu::weapon_chooser(newjog);
		return newjog;
	}
}  // namespace persman
}  // namespace CPP_RPG::Server