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

jogador::jogador(std::string &stname){
	jogador();
	name = stname;
}
jogador::jogador(){
	sk_life = sk_damage = sk_critcal = sk_actionpoints = sk_magicalpoints = money = 0;
}

jogador::~jogador(){
	std::cout<< "Jogador destructor" << std::endl;
}

void jogador::atack_round(){
	std::cout << "atack 1 or 2 ?: ";
	std::cout.flush();
	std::string atack;
	std::cin >> atack;
	int atack_i = stoi(atack)-1;
	if(atack_i > 1 || atack_i < 0) atack_i = 0;
	std::cout << "you selected: " << atack_i << " : " << aramas[atack_i]->get_full_name() << std::endl;
}

std::string jogador::get_name() {
	return name;
}

void jogador::create_loot() {}