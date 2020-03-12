#include "sala.hpp"
void sala::add_personagem(personagem *ps){
	dentro.push_back(ps);
}
void sala::round_loop(){
	bool cont = 1;
	while(cont){
		for(auto x : dentro){
			cout << x->get_name() << "'s life : " << x->get_life() << "\t\t";
		}
		cout << endl;
		for(auto x : dentro){
			std::cout << x->get_name() << "'s turn" << std::endl;
			personagem *recieve = dentro.back() == x ? dentro.front(): dentro.back();
			x->atack_round(recieve);
			if(!recieve->is_alive()){
				cont = 0;
				break;
			}
		}
		std::cout << "Round end" << endl << endl;
	};
	std::cout << "Battle end" << endl;
}
sala::sala(std::string &n_name){
	name = &n_name;
}
int sala::get_num_inside() {
	return dentro.size();
}