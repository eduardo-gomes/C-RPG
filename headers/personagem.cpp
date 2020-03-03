#pragma once
#include "personagem.hpp"
loot::loot(){
	noloot = 1;
	xp = 0;
	money = 0;
}
bool loot::has_loot(){
	return !noloot;
}
loot::~loot(){
	std::cout << "destroing loot" << std::endl;
}


personagem::personagem(){
	aramas[0] = new bow();
	aramas[1] = new sword();
	colectedxp = xp = 0;
	level = 1;
	df_life = df_damage = df_critical = df_actionpoints = df_magicalpoints = 10;
}
personagem::~personagem(){
	std::cout << "destroing a1 and a2" << std::endl;
	delete aramas[0];
	delete aramas[1];
}
void personagem::arma_set(weapon *nv, int pos){
	if(pos > 1 || pos < 0) pos = 1;
	delete aramas[pos];
	aramas[pos] = nv;
}
weapon* personagem::get_arma(int pos){
	if (pos > 1 || pos < 0)
		pos = 0;
	return aramas[pos];
}
int personagem::get_all_xp(){
	return colectedxp;
}
void personagem::add_xp(int add){
	xp += add;
	colectedxp += add;
	try_level_up();
}
void personagem::try_level_up(){
	if(xp >= xp_to_next_level()){
		xp -= xp_to_next_level();
		level ++;
	}
}
int personagem::get_level(){
	return level;
}
int personagem::xp_to_next_level(){
	if(level < 2) return 250;
	return 500 * (level * level) - (500 * level);
}
std::string personagem::get_name() {
	return "Null_name";
}