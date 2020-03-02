#pragma once
#include "weapon.hpp"
class loot{
	private:
		bool noloot;
		int xp;
		unsigned int money;
	public:
		loot();
		bool has_loot();
		int get_xp_loot();
		unsigned int get_money_loot();
		virtual void create_loot() = 0;
		virtual ~loot();
};

class personagem : public loot{
	protected:
		int xp, level, df_life, df_damage, df_critical, df_actionpoints, df_magicalpoints;
		weapon a1, a2;
	public:
		int get_level();
		int get_all_xp();
		int xp_to_next_level();
		void add_xp();//try lv up
		void recieve_damage_from(int, std::string);
		personagem();
		virtual ~personagem();
		virtual void atack_round() = 0;
		virtual std::string get_name();
};