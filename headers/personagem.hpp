#pragma once
#include "weapon.hpp"
class loot{
	private:
		bool noloot;
		int xp;
		unsigned int money;
	public:
		loot();
		bool has_loot() const;
		int get_xp_loot() const;
		unsigned int get_money_loot() const;
		virtual void create_loot() = 0;
		virtual ~loot();
		friend void from_json(const nlohmann::json & j, loot *p);
		friend void to_json(nlohmann::json &j, const loot *p);
};

class personagem : public loot{
	protected:
		int colectedxp, xp, level, life_max, life, df_damage, df_critical, df_actionpoints, df_magicalpoints;
		weapon *armas[2];
	public:
		void arma_set(weapon *, int);
		weapon* get_arma(int);
		int get_life() const;
		void set_life(int);
		void add_life(int);
		int sub_life(int);
		int get_level() const;
		int get_all_xp() const;
		int xp_to_next_level();
		int get_xp() const { return xp; }
		void add_xp(int);//try lv up
		void try_level_up();
		void recieve_damage_from(int, std::string);
		personagem();
		virtual ~personagem();
		virtual void atack_round() = 0;
		virtual void atack_round(personagem *) = 0;
		void atack(weapon *arma, personagem *j);
		virtual std::string get_name() = 0;
		int get_life_max() const { return life_max; }
		int get_df_damage() const { return df_damage; }
		int get_df_critical() const { return df_critical; }
		int get_df_actionpoints() const { return df_actionpoints; }
		int get_df_magicalpoints() const { return df_magicalpoints; }
		friend void to_json(nlohmann::json &j, const personagem *p);
		friend void from_json(const nlohmann::json &j, personagem *p);
};