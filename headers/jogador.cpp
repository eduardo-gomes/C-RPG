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
	life = life_max = 25;
	sk_life = sk_damage = sk_critcal = sk_actionpoints = sk_magicalpoints = 0;
	money = 0;
}

jogador::~jogador(){
	std::cout<< "Jogador destructor" << std::endl;
}

void jogador::atack_round(){
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
}

std::string jogador::get_name() {
	return name;
}

void jogador::create_loot() {}