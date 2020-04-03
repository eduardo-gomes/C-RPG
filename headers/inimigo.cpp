#include "inimigo.hpp"
inimigo::inimigo(){
	create_loot();
	armas[0] = std::shared_ptr<weapon>(new bow());
	armas[1] = std::shared_ptr<weapon>(new sword());
}
std::string inimigo::get_name() {
	return "IA_name";
}
void inimigo::atack_round(){
	cout << "nobody selected to atack from " << this->get_name() << endl;
}
void inimigo::atack_round(std::shared_ptr<personagem>& p) {
	std::cout << "IA goes here" << std::endl;
	atack(armas[0]->get_damage() > armas[1]->get_damage() ? armas[0] : armas[1], p);
}
void inimigo::create_loot(){
	set_loot_xp(75 * (level * level) + (int)ran_num_gen() % 150 * level);
	set_loot_money(150U * (unsigned int)(level * level) + (unsigned int)ran_num_gen() % 300 * (unsigned int)level);
}