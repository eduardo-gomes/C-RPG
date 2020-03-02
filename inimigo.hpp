#pragma once
#include "personagem.hpp"
class inimigo : public personagem{
	public:
		void atack_round(){
			std::cout << "IA goes here" << std::endl;
		}
		std::string get_name();
};