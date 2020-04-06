CXX=g++
CXXFLAGS=-std=c++17 -pedantic-errors -Wall -Wextra -Wsign-conversion -Werror -lpthread
SOUT=server

HDIR=headers
_DEPS=nlohmann/json.hpp sockets.hpp persman.hpp menu.hpp json_conversions.hpp sala.hpp weapon.hpp personagem.hpp jogador.hpp inimigo.hpp sala.cpp weapon.cpp personagem.cpp jogador.cpp inimigo.cpp
DEPS=$(patsubst %, $(HDIR)/%,$(_DEPS))

debug: $(DEPS)
	$(CXX) rpg.cpp -o $(SOUT) $(CXXFLAGS) -g
O3: $(DEPS)
	$(CXX) rpg.cpp -o $(SOUT) $(CXXFLAGS) -O3 -g
release: $(DEPS)
	$(CXX) rpg.cpp -o $(SOUT) $(CXXFLAGS) -O3
