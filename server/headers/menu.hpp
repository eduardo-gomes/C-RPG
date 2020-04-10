#include "headers.hpp"
namespace CPP_RPG::Server {

namespace menu {
	const int Options_count = 4;
	const std::string Options = (R"(
	{
		"choosenum":{
			"n": 1,
			"st": 0,
			"text": "Menu Choose an option:",
			"opts":[
				"Exit",
				"Enter room",
				"change name",
				"Boot room"
			]
		}
	}
)"_json.dump());
	const std::string weaponschoice = (R"(
	{
		"choosenum":{
			"n": 2,
			"st": 1,
			"text": "Choose two weapons:",
			"opts":[
				"Sword",
				"Bow",
				"Wand"
			]
		}
	}
)"_json.dump());
	const std::string chooseName = (R"(
	{
		"choosestr":{
			"text": "New Player name:"
		}
	}
)"_json.dump());
	const nlohmann::json weaponChoosed = R"(
	{
		"chooseresp": null
	}
)"_json;
	void choose(int opt, std::shared_ptr<jogador>& j) {
		int room_num = -1;
		switch (opt) {
			case 0:
				j->disconect();
				break;
			case 1:
				while (room_num < 0) {
					string chose = "Enter room number (0000-9999): ", s_num;
					j->get_socket()->sendtoclient(chose);
					while (j->get_socket()->isempty()) {
					}
					room_num = atoi(j->get_socket()->get().c_str());
					j->get_socket()->next();
					if (room_num > 9999 || room_num < 0)
						room_num = -1;
				}
				SALAS::enter_sala_jog(room_num, j);
				while (!j->sala_atual->get_has_ended()) {
					this_thread::sleep_for(chrono::milliseconds(250));
				}
				break;
			case 2:
				rename(j);
				break;
			case 3: {
				std::unique_ptr<sala> sala_bot = SALAS::create_sala_bot();
				auto jper = std::static_pointer_cast<personagem>(j);
				sala_bot->add_personagem(jper);
				sala_bot->start_round();
				while (!sala_bot->get_has_ended()) {
					this_thread::sleep_for(chrono::milliseconds(250));
				}
			}
			default:
				break;
		}  //switch
	}
	void menu(std::shared_ptr<jogador>& j) {
		int opt;
		while (1) {
			j->get_socket()->sendtoclient(Options);
			while (j->get_socket()->isempty()) {
				ISEMPTY_DELAY
			}
			opt = atoi(j->get_socket()->get().c_str());
			j->get_socket()->next();
			if (opt >= 0 && opt < Options_count) {
				choose(opt, j);
				break;
			}
		}
	}
	void rename(std::shared_ptr<jogador>& jog) {
		const std::shared_ptr<server_client_socket>& cliente = jog->get_socket();
		std::string nname;
		//cliente->clear_msg();
		cliente->sendtoclient(chooseName);
		while (cliente->isempty()) {
			ISEMPTY_DELAY
		}
		nname = cliente->get();
		cliente->next();
		jog->name = nname;
	}
	void weapon_chooser(std::shared_ptr<jogador>& jog) {
		const std::shared_ptr<server_client_socket>& cliente = jog->get_socket();
		cliente->clear_msg();
		std::shared_ptr<weapon> new_weapon;
		int pos = 0;
		int opt;
		std::string tosend;
		while (pos <= 1) {
			cliente->sendtoclient(weaponschoice);
			while (cliente->isempty()) {
				ISEMPTY_DELAY
			}
			opt = atoi(cliente->get().c_str());
			cliente->next();
			if (opt > 3 || opt < 1) opt = 1;
			switch (opt) {
				case 1:
					new_weapon = std::shared_ptr<weapon>(new sword());
					tosend = "You choose " + new_weapon->get_full_name();
					break;
				case 2:
					new_weapon = std::shared_ptr<weapon>(new bow());
					tosend = "You choose " + new_weapon->get_full_name();
					break;
				case 3:
					new_weapon = std::shared_ptr<weapon>(new wand());
					tosend = "You choose " + new_weapon->get_full_name();
					break;
				default:
					new_weapon = std::shared_ptr<weapon>(new sword());
					tosend = "Default " + new_weapon->get_full_name();
					break;
			}
			jog->arma_set(new_weapon, pos++);
			nlohmann::json resp = (weaponChoosed);
			resp["chooseresp"] = tosend;
			cliente->sendtoclient(resp.dump());
		}
	}
}  // namespace menu
}  // namespace CPP_RPG::Server