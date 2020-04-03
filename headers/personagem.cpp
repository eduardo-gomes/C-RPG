#pragma once
#include "personagem.hpp"
loot::loot(){
	noloot = 1;
	xp = 0;
	money = 0;
}
bool loot::has_loot() const{
	if(xp || money)
		return 1;
	return !noloot;
}
int loot::get_xp_loot() const{
	return xp;
}
unsigned int loot::get_money_loot() const{
	return money;
}
loot::~loot(){
	//std::cout << "destroing loot" << std::endl;
}


personagem::personagem(){
	//armas[0] = std::shared_ptr<weapon>(new bow()); now the menu take care of this;
	//armas[1] = std::shared_ptr<weapon>(new sword());
	colectedxp = xp = 0;
	level = 1;
	df_damage = df_critical = df_actionpoints = df_magicalpoints = 10;
	life = life_max = 20;
	socket = NULL_CLIENT;
}
personagem::~personagem(){
	//std::cout << "destroing a1 and a2" << std::endl;
	armas[0].reset();
	armas[1].reset();
}
void personagem::arma_set(std::shared_ptr<weapon>& nv, int pos){
	if(pos > 1 || pos < 0) pos = 1;
	armas[pos] = nv;
}
std::shared_ptr<weapon>& personagem::get_arma(int pos){
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
int personagem::sub_life(int slp){
	if(life - slp < 0){
		int olife = life;
		life = 0;
		return olife;
	}
	if(slp < 0)
		return 0;
	life -= slp;
	return slp;
}
void personagem::heal(){
	life = life_max;
}
std::shared_ptr<server_client_socket>& personagem::get_socket() {
	return socket;
}
void personagem::set_socket(std::shared_ptr<server_client_socket>& newsocket) {
	socket = newsocket;
}
void personagem::atack(std::shared_ptr<weapon>& arma, std::shared_ptr<personagem>& j) {
	cout << this->get_name() << " atacando : " << j->get_name() << " com : " << arma->get_full_name() << endl;
	statadd_given_damage(j->recieve_damage_from(arma->get_damage(), this->get_name()));//atack and stat
	if(!j->is_alive()){
		recieve_loot(j);
	}
}
int personagem::recieve_damage_from(int damage, std::string from){
	damage = this->sub_life(damage);
	std::string tosend;
	tosend = this->get_name();
	tosend += " received damage ";
	tosend += to_string(damage) ;
	tosend += " from ";
	tosend += from;
	tosend += '\n';
	sala_atual->sendall(tosend);
	statadd_recieved_damage(damage);
	return damage;
}