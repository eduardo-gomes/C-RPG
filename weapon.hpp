#pragma once
class weapon{
	private:
		int material, type, level, damage_df, damage_buff, precision, precision_buff;
	public:
		weapon();
		~weapon();
		int material_upgrade_cost();
		void material_upgrade();
		int level_upgrade_cost();
		void level_upgrade();
		int get_atack_precision();
		void add_precision_buff();
		int get_damage();
		void buff_end();
		int get_damage_buff();
		void add_damage_buff(int);
};