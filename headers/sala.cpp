#include "sala.hpp"
void sala::add_personagem(personagem *ps){
	dentro.push_back(ps);
}
void sala::add_personagem(personagem *ps, server_client_socket *out) {
	dentro.push_back(ps);
	outputall.push_back(out);
}
void sala::round_loop(){
	bool cont = 1;
	std::string slife = "'s life : ", sturn = "'s turn", tosend, endl = "\n";
	while(cont){
		for(auto x : dentro){
			tosend = x->get_name();
			tosend += slife;
			tosend += std::to_string(x->get_life());
			tosend += "\t\t";
			cout << tosend;
			for(auto y : outputall){
				y->sendtoclient(tosend);
			}
		}
		for (auto y : outputall) {
			y->sendtoclient(endl);
		}
		cout << endl;
		for(auto x : dentro){
			tosend = x->get_name();
			tosend += sturn;
			tosend += endl;
			for (auto y : outputall) {
				y->sendtoclient(tosend);
			}
			cout << tosend;
			personagem *recieve = dentro.back() == x ? dentro.front(): dentro.back();
			x->atack_round(recieve);
			if(!recieve->is_alive()){
				cont = 0;
				break;
			}
		}
		tosend = "Round end";tosend = endl;
		for (auto y : outputall) {
			y->sendtoclient(tosend);
		}
		cout << tosend;
	}
	tosend = "Battle end";
	tosend += endl;
	for (auto y : outputall) {
		y->sendtoclient(tosend);
	}
	cout << tosend;
}
sala::sala(std::string &n_name){
	name = &n_name;
}
int sala::get_num_inside() {
	return dentro.size();
}