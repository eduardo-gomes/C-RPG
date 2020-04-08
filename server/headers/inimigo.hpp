#pragma once
#include "personagem.hpp"
namespace CPP_RPG::Server {

class inimigo : public personagem {
	public:
	inimigo();
	std::pair<int, int> atack_round(std::shared_ptr<personagem>&);
	//int atack_round();
	std::string get_name();
	void create_loot();
};
}  // namespace CPP_RPG::Server