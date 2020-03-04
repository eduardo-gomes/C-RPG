#include "sala.hpp"
void sala::add_personagem(personagem *ps){
	dentro.push_back(ps);
}
void sala::round_loop(){
	for(auto x : dentro){
		cout << x->get_name() << "'s life : " << x->get_life() << "\t\t";
	}
	cout << endl;
	for(auto x : dentro){
		std::cout << x->get_name() << "'s turn" << std::endl;
		x->atack_round(dentro.back());
	}
	std::cout << "Round end" << endl << endl;
}
sala::sala(std::string &n_name){
	name = &n_name;
}