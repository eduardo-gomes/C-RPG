#include "inimigo.hpp"
inimigo::inimigo(){
	create_loot();
	armas[0] = std::shared_ptr<weapon>(new bow());
	armas[1] = std::shared_ptr<weapon>(new sword());
}
std::string inimigo::get_name() {
	return "IA_name";
}
/*int inimigo::atack_round(){
	cout << "nobody selected to atack from " << this->get_name() << endl;
}*/
std::pair<int, int> inimigo::atack_round(std::shared_ptr<personagem>& p) {
	std::cout << "IA goes here" << std::endl;
	int arma_pos = armas[0]->get_damage() > armas[1]->get_damage() ? 0 : 1;
	return make_pair(atack(armas[arma_pos], p), arma_pos);
}
void inimigo::create_loot(){
	set_loot_xp(75 * (level * level) + (int)ran_num_gen() % 150 * level);
	set_loot_money(150U * (unsigned int)(level * level) + (unsigned int)ran_num_gen() % 300 * (unsigned int)level);
}