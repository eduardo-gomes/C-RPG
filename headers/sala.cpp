#include "sala.hpp"
void sala::add_personagem(personagem *ps){
	mtx_to_dentro.lock();
	to_dentro.push_back(ps);
	mtx_to_dentro.unlock();
	ps->sala_atual = this;
	has_ended = 0;
	std::string tosend = "Jogador: ";
	tosend += ps->get_name();
	tosend += " entrou\n";
	sendall(tosend);
}
/*void sala::add_personagem(personagem *ps, server_client_socket *out) {
	outputall.push_back(out);
	add_personagem(ps);
}*/
void sala::round_loop(){
	int cont = 2;
	std::string slife = "'s life : ", sturn = "'s turn", tosend, endl = "\n";
	while(cont){
		while(dentro.size() < 2){
			if(!to_dentro.empty()){
				mtx_to_dentro.lock();
				for(auto x : to_dentro){
					dentro.push_back(x);
				}
				to_dentro.clear();
				mtx_to_dentro.unlock();
			}
		}
		tosend.clear();
		for(auto x : dentro){
			tosend += x->get_name();
			tosend += slife;
			tosend += std::to_string(x->get_life());
			tosend += "\t\t";
			/*std::cout << tosend;
			sendall(tosend);*/
		}
		tosend += '\n';
		sendall(tosend);
		std::cout << tosend;
		for(auto x : dentro){
			tosend = endl;
			tosend += x->get_name();
			tosend += sturn;
			tosend += endl;
			sendall(tosend);
			std::cout << tosend;
			personagem *recieve = dentro.back() == x ? dentro.front(): dentro.back();
			x->atack_round(recieve);
			if(!recieve->is_alive()){
				cont--;
				break;
			}
		}
		tosend = "Round end\n";
		sendall(tosend);
		std::cout << tosend;
	}
	tosend = "Battle end";
	tosend += endl;
	sendall(tosend);
	std::cout << tosend;
	has_ended = 1;
	//outputall.clear();
}
sala::sala(){
	//std::string una = "Unammed sala";
	name = new std::string("Unammed sala");
	has_ended = 1;
}
sala::sala(std::string &n_name) : sala() {
	name = &n_name;
}
int sala::get_num_inside() {
	return dentro.size() + to_dentro.size();
}
void sala::start_round(){
	if(has_ended){
		for(auto it = dentro.begin(); it != dentro.end(); ++it){
			if((*it)->is_jogador()){
				it = dentro.erase(it);
				if(it == dentro.end()) break;
			}else (*it)->heal();
		}
		has_ended = 0;
	}
	if(!has_ended){
		has_started = 1;
		std::thread([this] {this->round_loop();}).detach();///(this->round_loop).detach();
	}
}

void sala::sendall(std::string &send){
	for (auto y : dentro) {
		y->get_socket()->sendtoclient(send);
	}
}

void sala::clear_room(){
	dentro.clear();
}

bool sala::get_has_ended(){
	return has_ended;
}







sala* SALAS::create_sala_bot(int num) {
	sala *s = get_sala(num);
	s->add_personagem(new inimigo());
	return s;
}
void SALAS::enter_sala(int &num, personagem* pers){
	sala *s = get_sala(num);
	s->add_personagem(pers);
	/*while(1){
		if(s->get_num_inside() > 1){
			s->round_loop();
			break;
		}
	}*/
	if ((!s->get_has_started() && !s->get_has_ended()) || s->get_has_ended()) s->start_round();
	return;
}
/*void SALAS::enter_sala(int &num, personagem *pers, server_client_socket *out) {
	sala *s = get_sala(num);
	s->add_personagem(pers, out);
	if ((!s->get_has_started() && !s->get_has_ended()) || s->get_has_ended()) s->start_round();
	return;
}*/
sala* SALAS::get_sala(int &num) {
	if (salas_lista.find(num) == salas_lista.end()) {
		std::string num_s = std::to_string(num);
		num_s = std::string(4 - num_s.length(), '0').append(num_s);
		return salas_lista[num] = new sala(num_s);
	}
	return salas_lista.find(num)->second;
}