#pragma once
#include "headers.hpp"
class sala{
	private:
		bool has_ended, has_started;
		std::string* name;
		std::deque<std::shared_ptr<personagem>> dentro;
		std::deque<std::shared_ptr<personagem>> to_dentro;
		std::mutex mtx_to_dentro;
		//std::deque<server_client_socket *> outputall;
	public:
		bool get_has_ended();
		bool get_has_started(){return has_started;}
		void clear_room();
		void sendall(std::string &);
		void round_loop();
		void add_personagem(std::shared_ptr<personagem>&);
		//void add_personagem(personagem *, server_client_socket *);
		sala();
		sala(std::string &);
		int get_num_inside();
		void start_round();
};
typedef class sala sala;//vscode sala is not a type name

namespace SALAS {
	std::map<int, sala *> salas_lista;
	sala *get_sala(int &num);
	sala *create_sala_bot(int num);
	void enter_sala(int &num, std::shared_ptr<personagem> &pers);
	void enter_sala_jog(int &num, std::shared_ptr<jogador> &pers){
		auto copy = std::static_pointer_cast<personagem>(pers);
		enter_sala(num, copy);
	}
}	// namespace SALAS