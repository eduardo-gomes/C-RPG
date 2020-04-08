#pragma once
namespace CPP_RPG::Server {
namespace weapon_T {
	const int BOW = 1;
	const int SWORD = 2;
	const int WAND = 3;
	const std::string materials[10] = {"papel", "madeira", "pedra", "aluminio", "ferro", "rubi", "diamante", "titanio", "materia negra", "GINSU 2000"};
	const int material_max = 9;
}  // namespace weapon_T
class weapon {
	protected:
	int material, /*level,*/ xp, damage_df, damage_buff, precision, precision_buff;

	public:
	weapon();
	virtual ~weapon();
	int material_upgrade_cost();
	void material_upgrade();
	/*int level_upgrade_cost();
		void level_upgrade();*/
	int get_atack_precision();
	void add_precision_buff(int);
	int get_damage();
	void buff_end();
	int get_damage_buff();
	void add_damage_buff(int);
	int get_xp();
	void add_xp(int);
	const std::string &get_material_name();
	virtual int get_tipo() const;
	virtual std::string get_tipo_st();
	std::string get_full_name();
	friend void to_json(nlohmann::json &j, const weapon *p);
	friend void from_json(const nlohmann::json &j, std::shared_ptr<weapon> &p);
};

class bow : public weapon {
	public:
	bow();
	int get_tipo() const;
	std::string get_tipo_st();
};

class sword : public weapon {
	public:
	sword();
	int get_tipo() const;
	std::string get_tipo_st();
};

class wand : public weapon {
	public:
	wand();
	int get_tipo() const;
	std::string get_tipo_st();
};
}  // namespace CPP_RPG::Server