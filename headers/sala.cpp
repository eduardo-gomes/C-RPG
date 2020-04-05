#include "sala.hpp"
void to_json(nlohmann::json& j, const sala_round_action& from);
void sala::add_personagem(std::shared_ptr<personagem>& ps){
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
void sala::round_loop(){
	int cont = 1;
	std::string slife = "'s life : ", sturn = "'s turn", tosend, endl = "\n";
	while(dentro.size() < 2 || !to_dentro.empty()){
		if(!to_dentro.empty()){
			mtx_to_dentro.lock();
			for(auto x : to_dentro){
				dentro.push_back(x);
			}
			to_dentro.clear();
			mtx_to_dentro.unlock();
		}
	}
	nlohmann::json j;
	to_json(j, get_sala_players());
	for(unsigned pos = 0; pos < dentro.size(); ++pos){
		dentro.at(pos)->get_socket()->sendtoclient(get_sala_players_pos(pos, j).dump());
	}
	sala_round_action round_action;
	std::pair<int, int> atack_ret;
	while(cont){
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
		for(auto it = dentro.begin(); it != dentro.end(); ++it){
			tosend = endl;
			tosend += (*it)->get_name();
			tosend += sturn;
			tosend += endl;
			sendall(tosend);
			std::cout << tosend;
			auto recieve = (dentro.back() == (*it)) ? dentro.begin(): dentro.begin()+1;
			// TODO ask personagem who wants to atack
			atack_ret = (*it)->atack_round(*recieve);
			round_action.action_type = 0;
			round_action.from = std::distance(dentro.begin(), it);
			round_action.to = std::distance(dentro.begin(), recieve);
			round_action.damage = atack_ret.first;
			round_action.weapon_pos = atack_ret.second;
			tosend = nlohmann::json(round_action).dump() + '\n'; 
			sendall(tosend);
			if(!(*recieve)->is_alive()){
				tosend = (*recieve)->get_name();
				tosend += " died\n";
				sendall(tosend);
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
	//has_ended = 1;
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

sala_players sala::get_sala_players(){
	sala_players sala;
	sala.dentro = &dentro;
	return sala;
}
nlohmann::json& sala::get_sala_players_pos(unsigned n, nlohmann::json& j){
	j["your_posi"] = n;
	return j;
}






std::unique_ptr<sala> SALAS::create_sala_bot() {
	std::unique_ptr<sala> s (new sala());
	auto temp = std::static_pointer_cast<personagem>(std::shared_ptr<inimigo>(new inimigo()));
	s->add_personagem(temp);
	return s;
}
void SALAS::enter_sala(int &num, std::shared_ptr<personagem>& pers){
	std::shared_ptr<sala> &s = get_sala(num);
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
std::shared_ptr<sala>& SALAS::get_sala(int &num) {
	if (salas_lista.find(num) == salas_lista.end()) {
		std::string num_s = std::to_string(num);
		num_s = std::string(4 - num_s.length(), '0').append(num_s);
		return salas_lista[num] = std::shared_ptr<sala> (new sala(num_s));
	}
	return salas_lista.find(num)->second;
}