#pragma once
#include "personagem.hpp"
class inimigo : public personagem{
	public:
		void atack_round(personagem *);
		void atack_round();
		std::string get_name();
		void create_loot();
};