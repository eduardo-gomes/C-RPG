#pragma once
#include "headers.hpp"
class sala{
	private:
		std::string* name;
		std::deque<personagem *> dentro;
	public:
		void round_loop();
		void add_personagem(personagem *);
		sala(std::string &);
};