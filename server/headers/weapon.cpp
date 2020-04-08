#include "weapon.hpp"

#include "headers.hpp"
using namespace std;
namespace CPP_RPG::Server {
namespace bow_ {
	const int damage_df = 7;
	const int precision = 950;
}  // namespace bow_
namespace sword_ {
	const int damage_df = 13;
	const int precision = 980;
}  // namespace sword_
namespace wand_ {
	const int damage_df = 10;
	const int precision = 993;
}  // namespace wand_

weapon::weapon() {
	material = 0;
	//level = 0;
	xp = 100;
	damage_df = 3;
	damage_buff = 0;
}
weapon::~weapon() {}
int weapon::get_tipo() const {
	return 0;
}
const std::string& weapon::get_material_name() {
	return weapon_T::materials[material];
}
std::string weapon::get_full_name() {
	string rt = get_material_name();
	rt += ' ';
	rt += get_tipo_st();
	return rt;
}
std::string weapon::get_tipo_st() {
	return "undefined weapon with damage 3";
}
int weapon::material_upgrade_cost() {  ///////////////////////////////////////////////////////////////////////TODO
	if (material >= weapon_T::material_max)
		return -1;
	return 326 * (int)ceil(pow(material, 4)) - 200 * material + 10;
}
void weapon::material_upgrade() {
	if (material_upgrade_cost() <= xp && material < weapon_T::material_max) {
		xp -= material_upgrade_cost();
		material++;
	}
}
/*int weapon::level_upgrade_cost(){return 0;}////MSVC
void weapon::level_upgrade(){}*/
int weapon::get_atack_precision() {
	return precision + precision_buff > 1000 ? 1000 : precision + precision_buff;
}
void weapon::add_precision_buff(int add) {
	precision_buff += add;
}
int weapon::get_damage() {
	return (damage_df + damage_buff) * ((material + 1) * (material + 1));
}
void weapon::buff_end() {
	precision_buff = damage_buff = 0;
}
int weapon::get_damage_buff() {
	return damage_buff;
}
void weapon::add_damage_buff(int add) {
	damage_buff += add;
}
int weapon::get_xp() {
	return xp;
}
void weapon::add_xp(int add) {
	xp += add;
}

bow::bow() {
	damage_df = bow_::damage_df;
	precision = bow_::precision;
}
int bow::get_tipo() const {
	return weapon_T::BOW;
}
std::string bow::get_tipo_st() {
	return "bow";
}

sword::sword() {
	damage_df = sword_::damage_df;
	precision = sword_::precision;
}
int sword::get_tipo() const {
	return weapon_T::SWORD;
}
std::string sword::get_tipo_st() {
	return "sword";
}

wand::wand() {
	damage_df = wand_::damage_df;
	precision = wand_::precision;
}
int wand::get_tipo() const {
	return weapon_T::WAND;
}
std::string wand::get_tipo_st() {
	return "wand";
}
}  // namespace CPP_RPG::Server