#include "jogador.hpp"

jogador::jogador(std::string n_name){
	std::cout << "Insert name: ";
	std::cout.flush();
	std::cin >> name;
	std::cout << name << std::endl;
}

jogador::~jogador(){
	std::cout<< "Jogador destructor" << std::endl;
}

void jogador::atack_round(){
	std::cout << "atack 1 or 2 ?: ";
	std::cout.flush();
	std::string atack;
	std::cin >> atack;
	std::cout << "you selected: " << atack << std::endl;
}

std::string jogador::get_name() {
	return name;
}

void jogador::create_loot() {}