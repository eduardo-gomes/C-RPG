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
		void atack_round(personagem *);
		~jogador();
		jogador();
		jogador(std::string &);
		unsigned int get_money() const { return money; }
		int get_sk_life() const { return sk_life; }
		int get_sk_damage() const { return sk_damage; }
		int get_sk_critcal() const { return sk_critcal; }
		int get_sk_actionpoints() const { return sk_actionpoints; }
		int get_sk_magicalpoints() const { return sk_magicalpoints; }
		friend void from_json(const nlohmann::json &j, jogador &p);
		friend void to_json(nlohmann::json &j, const jogador &p);
};