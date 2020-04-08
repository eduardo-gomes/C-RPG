#pragma once
#include "headers.hpp"
namespace CPP_RPG::Server {
struct sala_players;
void to_json(nlohmann::json &j, const sala_players &from);
class sala {
	private:
	bool has_ended, has_started;
	std::string *name;
	std::deque<std::shared_ptr<personagem>> dentro;
	std::deque<std::shared_ptr<personagem>> to_dentro;
	std::mutex mtx_to_dentro;
	//std::deque<server_client_socket *> outputall;
	public:
	bool get_has_ended();
	bool get_has_started() { return has_started; }
	void clear_room();
	void sendall(std::string &);
	void round_loop();
	void add_personagem(std::shared_ptr<personagem> &);
	//void add_personagem(personagem *, server_client_socket *);
	sala();
	sala(std::string &);
	int get_num_inside();
	void start_round();
	sala_players get_sala_players();
	nlohmann::json &get_sala_players_pos(unsigned, nlohmann::json &);
};
struct sala_players {
	std::deque<std::shared_ptr<personagem>> *dentro;
	unsigned your_pos;
};
/*struct sala_player_enter{ //can't enter after the round begin now
	std::shared_ptr<personagem> entrou;
	unsigned enter_pos;
};*/
struct sala_round {	 //to be implemented
	int round_num, now_atack;
};
struct sala_round_action {
	int action_type, damage;
	unsigned from, to;
	int weapon_pos;
};

namespace SALAS {
	std::map<int, std::shared_ptr<sala>> salas_lista;
	std::shared_ptr<sala> &get_sala(int &num);
	std::unique_ptr<sala> create_sala_bot();
	void enter_sala(int &num, std::shared_ptr<personagem> &pers);
	void enter_sala_jog(int &num, std::shared_ptr<jogador> &pers) {
		auto copy = std::static_pointer_cast<personagem>(pers);
		enter_sala(num, copy);
	}
}  // namespace SALAS
}  // namespace CPP_RPG::Server