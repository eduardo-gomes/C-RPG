#pragma once
#include "personagem.hpp"
loot::loot(){
	noloot = 1;
	xp = money = 0;
}
bool loot::has_loot(){
	return !noloot;
}
loot::~loot(){
	std::cout << "destroing loot" << std::endl;
};


personagem::personagem(){
	aramas[0] = new bow();
	aramas[1] = new sword();
	xp = level = 0;
	df_life = df_damage = df_critical = df_actionpoints = df_magicalpoints = 10;
}
personagem::~personagem(){
	std::cout << "destroing a1 and a2" << std::endl;
	delete aramas[0], aramas[1];
};
void personagem::arma_set(weapon *nv, int pos){
	if(pos > 1 || pos < 0) pos = 1;
	delete aramas[pos];
	aramas[pos] = nv;
}
int personagem::get_all_xp(){
	return 500 * (level + (level + 1) * level) - (500 * ( ( (1 + level) * level) / 2) ) + xp;
}
int personagem::xp_to_next_level(){
	return 500 * (level * level) - (500 * level);
}
std::string personagem::get_name() {
	return "Null_name";
}