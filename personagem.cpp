#pragma once
#include "personagem.hpp"
loot::loot(){
	noloot = 1;
}
bool loot::has_loot(){
	return !noloot;
}
loot::~loot(){
	std::cout << "destroing loot" << std::endl;
};


personagem::personagem(){}
personagem::~personagem(){
	std::cout << "destroing a1 and a2" << std::endl;
	delete &a1, &a2;
};

int personagem::get_all_xp(){
	return 500 * (level + (level + 1) * level) - (500 * ( ( (1 + level) * level) / 2) ) + xp;
}
int personagem::xp_to_next_level(){
	return 500 * (level * level) - (500 * level);
}
std::string personagem::get_name() {
	return "Null_name";
}