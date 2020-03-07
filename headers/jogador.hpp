#pragma once
#include "personagem.hpp"
class jogador : public personagem{
	private:
		std::string name;
		unsigned int money;
		int sk_life, sk_damage, sk_critcal, sk_actionpoints, sk_magicalpoints;
		unsigned int damage_given, damage_taken, enemies_killeds;
		unsigned int damage_given_all, damage_taken_all, enemies_killeds_all, deaths;
	public:
		virtual bool is_jogador() { return 1; };
		std::string get_name();
		void create_loot();
		void atack_round();
		void atack_round(personagem *);
		void statadd_recieved_damage(int);
		void statadd_given_damage(int);
		void recieve_loot(personagem *);
		void on_death();
		~jogador();
		jogador();
		jogador(std::string &);
		unsigned int get_money() const { return money; }
		int get_sk_life() const { return sk_life; }
		int get_sk_damage() const { return sk_damage; }
		int get_sk_critcal() const { return sk_critcal; }
		int get_sk_actionpoints() const { return sk_actionpoints; }
		int get_sk_magicalpoints() const { return sk_magicalpoints; }
		friend void from_json(const nlohmann::json &j, jogador *p);
		friend void to_json(nlohmann::json &j, const jogador *p);
};