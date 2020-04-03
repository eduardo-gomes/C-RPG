#pragma once
#include "personagem.hpp"
class inimigo : public personagem{
	public:
		inimigo();
		void atack_round(std::shared_ptr<personagem>&);
		void atack_round();
		std::string get_name();
		void create_loot();
};