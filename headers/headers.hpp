#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include <deque>
#include <cmath>
#include <map>
std::knuth_b ran_num_gen(140601);
#include "nlohmann/json.hpp"
#define ISEMPTY_DELAY std::this_thread::sleep_for(std::chrono::milliseconds(50));
volatile bool continue_running = 1;
#include "sockets.hpp"
//#include "weapon.hpp"
#include "weapon.cpp"
class sala;
#include "personagem.hpp" //needed for sala.hpp
#include "jogador.hpp" //needed for sala.hpp
#include "sala.hpp"//needed for personagem.cpp
#include "personagem.cpp"
#include "jogador.cpp"
//#include "inimigo.hpp"
#include "inimigo.cpp"
#include "sala.cpp"
#include "persman.hpp"
#include "menu.hpp"
#include "json_conversions.hpp"
