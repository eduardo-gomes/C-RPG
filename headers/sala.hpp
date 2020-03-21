#pragma once
#include "headers.hpp"
class sala{
	private:
		std::string* name;
		std::deque<personagem *> dentro;
		std::deque<server_client_socket *> outputall;
	public:
		void round_loop();
		void add_personagem(personagem *);
		void add_personagem(personagem *, server_client_socket *);
		sala(std::string &);
		int get_num_inside();
};

class SALAS{
	private:
		std::map<int, sala*> salas_lista;
	public:
		sala* get_sala(int &num){
			if(salas_lista.find(num) == salas_lista.end()){
				std::string num_s = std::to_string(num);
				num_s = std::string(4 - num_s.length(), '0').append(num_s);
				return salas_lista[num] = new sala(num_s);
			}
			return salas_lista.find(num)->second;
		}
		sala* create_sala_bot(int num){
			sala* s = get_sala(num);
			s->add_personagem(new inimigo());
			return s;
		}
		void enter_sala(int &num, personagem* pers){
			sala *s = get_sala(num);
			s->add_personagem(pers);
			while(1){
				if(s->get_num_inside() > 1){
					s->round_loop();
					break;
				}
			}
			return;
		}
		void enter_sala(int &num, personagem *pers, server_client_socket *out) {
			sala *s = get_sala(num);
			s->add_personagem(pers, out);
			while (1) {
				if (s->get_num_inside() > 1) {
					s->round_loop();
					break;
				}
			}
			return;
		}
};