#include "headers.hpp"
#include "weapon.hpp"
weapon::weapon(){
	material = 0;
	type = 0;
	level = 0;
	damage_df = 3;
	damage_buff = 0;
}
weapon::~weapon() {}