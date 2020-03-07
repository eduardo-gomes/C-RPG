#include "jogador.hpp"

/*
Player classe	atCorpo	atArq	at_Magi	
Arqueiro		+20%	+50%	+0%		
guerreiro		+50%	+0%		+0%		
mago			+0%		+10%	+100%	
				dfCorpo	dfArq	df_Magi	
Arqueiro		+20%	+40%	+0%		
guerreiro		+50%	+0%		+0%		
mago			+10%	+10%	+50%	

materiais = [papel, madeira, pedra, aluminio, ferro, rubi, diamante, titanio, materia negra]


*/

jogador::jogador(std::string &stname) : jogador(){
	name = stname;
}
jogador::jogador(){
	life = life_max = 9999;
	sk_life = sk_damage = sk_critcal = sk_actionpoints = sk_magicalpoints = 0;
	deaths = damage_given_all = damage_taken_all = enemies_killeds_all = damage_given = damage_taken = enemies_killeds = money = 0;
}

jogador::~jogador(){
	std::cout<< "Jogador destructor" << std::endl;
}

void jogador::atack_round(){
	cout << "nobody selected to atack from " << this->get_name() << endl;
}
void jogador::atack_round(personagem *toatk){
	std::cout << "atack 1 :" << armas[0]->get_full_name() << " or 2 : " << armas[1]->get_full_name() << " ?: ";
	std::cout.flush();
	std::string atack;
	std::cin >> atack;
	int atack_i;
	try{
	atack_i = stoi(atack) - 1;
	}
	catch(std::invalid_argument& e){
		atack_i = 0;
		cout << "invalid argument" << endl;
	}
	if(atack_i > 1 || atack_i < 0) atack_i = 0;
	std::cout << "you selected: " << atack_i + 1 << " : " << armas[atack_i]->get_full_name() << std::endl;
	std::cout << "damage: " << armas[atack_i]->get_damage() << " precision : " << armas[atack_i]->get_atack_precision() << endl;
	this->atack(armas[atack_i], toatk);
	if(!toatk->is_alive()){
		enemies_killeds++;
		enemies_killeds_all++;
	}
}

std::string jogador::get_name() {
	return name;
}

void jogador::create_loot() {
	set_loot_xp((int)damage_given * level - (int)damage_taken/4 * level + 75 * (level * level));
	set_loot_money(150U * (unsigned int)(level * level));
}

void jogador::statadd_recieved_damage(int rec_dmg){
	damage_taken += (unsigned int)rec_dmg;
	damage_taken_all += (unsigned int)rec_dmg;
	if(!life)
		on_death();
}
void jogador::statadd_given_damage(int giv_dmg){
	damage_given += (unsigned int)giv_dmg;
	damage_given_all += (unsigned int)giv_dmg;
}

void jogador::on_death(){
	create_loot();
	damage_taken = damage_given = enemies_killeds = 0;
	deaths++;
}

void jogador::recieve_loot(personagem *j){
	xp += j->get_xp_loot();
	money += j->get_money_loot();
	cout << get_name() << " recieved " << j->get_xp_loot() << " xp and $" << j->get_money_loot() << " from " << j->get_name() << "'s loot" << endl;
}