#pragma once
#include "personagem.hpp"
class jogador : public personagem{
	private:
		std::string name;
		unsigned int money;
		int sk_life, sk_damage, sk_critcal, sk_actionpoints, sk_magicalpoints;
	public:
		std::string get_name();
		void create_loot();
		void atack_round();
		~jogador();
		jogador();
		jogador(std::string &);
};