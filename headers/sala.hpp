#pragma once
#include "headers.hpp"
class sala{
	private:
		bool has_ended, has_started;
		std::string* name;
		std::deque<personagem *> dentro;
		std::deque<personagem *> to_dentro;
		std::mutex mtx_to_dentro;
		std::deque<server_client_socket *> outputall;
	public:
		bool get_has_ended();
		bool get_has_started(){return has_started;}
		void clear_room();
		void sendall(std::string &);
		void round_loop();
		void add_personagem(personagem *);
		void add_personagem(personagem *, server_client_socket *);
		sala();
		sala(std::string &);
		int get_num_inside();
		void start_round();
};
typedef class sala sala;//vscode sala is not a type name

class SALAS{
	private:
		std::map<int, sala*> salas_lista;
	public:
		sala* get_sala(int &num);
		sala* create_sala_bot(int num);
		void enter_sala(int &num, personagem* pers);
		void enter_sala(int &num, personagem *pers, server_client_socket *out);
};