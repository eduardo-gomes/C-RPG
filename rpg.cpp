#include "headers.hpp"
using namespace std;

int main(){
	personagem *pl = new jogador("jota1");
	string sn = "sala1";
	sala sala1(sn);
	sala1.add_personagem(pl);
	sala1.round_loop();
	sala1.round_loop();
}