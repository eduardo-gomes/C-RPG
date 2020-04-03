#include "headers.hpp"

namespace menu {
	const int Options_count = 4;
	const std::string Options = R"(Menu Choose an option:
	1- Enter room
	2- change name (WIP)
	3- Boot room (WIP)

	0- Exit
)";
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
			default:
				break;
		}  //switch
	}
	void menu(std::shared_ptr<jogador>& j) {
		int opt;
		std::string tosend = Options;
		while (1) {
			j->get_socket()->sendtoclient(tosend);
			while (j->get_socket()->isempty()) {
				this_thread::sleep_for(chrono::milliseconds(50));
			}
			opt = atoi(j->get_socket()->get().c_str());
			j->get_socket()->next();
			if (opt >= 0 && opt < Options_count) {
				choose(opt, j);
				break;
			}
		}
	}
}  // namespace menu