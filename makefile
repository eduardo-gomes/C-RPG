CXX=g++
CXXFLAGS=-std=c++17 -pedantic-errors -Wall -Wextra -Wsign-conversion -Werror -lpthread -Iinclude $(FLAGS)
SOUT=server.exe

HDIR=server/headers
_DEPS=sockets.hpp persman.hpp menu.hpp json_conversions.hpp sala.hpp weapon.hpp personagem.hpp jogador.hpp inimigo.hpp sala.cpp weapon.cpp personagem.cpp jogador.cpp inimigo.cpp
DEPS=$(patsubst %, $(HDIR)/%,$(_DEPS))
SFILE=server/server.cpp

#LINK?=http://localhost:8081
#LINK:=\"$(LINK)\"
ifdef LINK
CXXFLAGS+= -DLINK=$(LINK)
endif

debug: $(DEPS)
	$(CXX) $(SFILE) -o $(SOUT) $(CXXFLAGS) -g -Og
O3: $(DEPS)
	$(CXX) $(SFILE) -o $(SOUT) $(CXXFLAGS) -O3 -g
release: $(DEPS)
	$(CXX) $(SFILE) -o $(SOUT) $(CXXFLAGS) -O3
