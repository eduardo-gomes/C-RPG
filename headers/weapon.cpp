#include "headers.hpp"
#include "weapon.hpp"
using namespace std;
namespace bow_{
	const int damage_df = 7;
	const int precision = 950;
};
namespace sword_{
	const int damage_df = 13;
	const int precision = 980;
};
namespace wand_{
	const int damage_df = 10;
	const int precision = 993;
};

weapon::weapon(){
	material = 0;
	level = 0;
	damage_df = 3;
	damage_buff = 0;
}
weapon::~weapon() {}
int weapon::get_tipo(){
	return 0;
}
std::string* weapon::get_material_name(){
	return &weapon_T::materials[material];
}
std::string weapon::get_full_name(){
	string rt = *get_material_name();
	rt += ' ';
	rt += get_tipo_st();
	return rt;
}
std::string weapon::get_tipo_st(){
	return "undefined weapon with damage 3";
}
int weapon::material_upgrade_cost(){}///////////////////////////////////////////////////////////////////////TODO
void weapon::material_upgrade(){}
int weapon::level_upgrade_cost(){}
void weapon::level_upgrade(){}
int weapon::get_atack_precision(){}
void weapon::add_precision_buff(){}
int weapon::get_damage(){}
void weapon::buff_end(){}
int weapon::get_damage_buff(){}
void weapon::add_damage_buff(int) {} ///////////////////////////////////////////////////////////////////////

bow::bow(){
	damage_df = bow_::damage_df;
	precision = bow_::precision;
}
int bow::get_tipo(){
	return weapon_T::BOW;
}
std::string bow::get_tipo_st(){
	return "bow";
}

sword::sword(){
	damage_df = sword_::damage_df;
	precision = sword_::precision;
}
int sword::get_tipo(){
	return weapon_T::SWORD;
}
std::string sword::get_tipo_st(){
	return "sword";
}

wand::wand(){
	damage_df = wand_::damage_df;
	precision = wand_::precision;
}
int wand::get_tipo(){
	return weapon_T::WAND;
}
std::string wand::get_tipo_st(){
	return "wand";
}