#include "sala.hpp"
void sala::add_personagem(personagem *ps){
	dentro.push_back(ps);
}
void sala::round_loop(){
	for(auto x : dentro){
		std::cout << x->get_name() << "'s turn" << std::endl;
		x->atack_round();
	}
}
sala::sala(std::string &n_name){
	name = &n_name;
}