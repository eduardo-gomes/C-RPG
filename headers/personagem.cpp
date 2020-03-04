#pragma once
#include "personagem.hpp"
loot::loot(){
	noloot = 1;
	xp = 0;
	money = 0;
}
bool loot::has_loot() const{
	return !noloot;
}
int loot::get_xp_loot() const{
	return xp;
}
unsigned int loot::get_money_loot() const{
	return money;
}
loot::~loot(){
	std::cout << "destroing loot" << std::endl;
}


personagem::personagem(){
	armas[0] = new bow();
	armas[1] = new sword();
	colectedxp = xp = 0;
	level = 1;
	df_damage = df_critical = df_actionpoints = df_magicalpoints = 10;
	life = life_max = 20;
}
personagem::~personagem(){
	std::cout << "destroing a1 and a2" << std::endl;
	delete armas[0];
	delete armas[1];
}
void personagem::arma_set(weapon *nv, int pos){
	if(pos > 1 || pos < 0) pos = 1;
	delete armas[pos];
	armas[pos] = nv;
}
weapon* personagem::get_arma(int pos){
	if (pos > 1 || pos < 0)
		pos = 0;
	return armas[pos];
}
int personagem::get_all_xp() const{
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
int personagem::get_level() const{
	return level;
}
int personagem::xp_to_next_level(){
	if(level < 2) return 250;
	return 500 * (level * level) - (500 * level);
}
std::string personagem::get_name() {
	return "Null_name";
}

int personagem::get_life() const{
	return life;
}
void personagem::set_life(int nlp){
	if(nlp > life_max)
		nlp = life;
	if(nlp < 0)
		nlp = 0;
}
void personagem::add_life(int plp){
	if(plp + life > life_max){
		life = life_max;
		return;
	}
	if(plp < 0)
		return;
	life += plp;
}
void personagem::sub_life(int slp){
	if(life - slp < 0){
		life = 0;
		return;
	}
	if(slp < 0)
		return;
	life -= slp;
}