// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

#include "Game.h"
#include "GameObject.h"
#include "Resource.h"


int main(int, char**) {
	if (Game::Init()) {
		Game::Instance()->start(10);
	}

	// Escribir estadísticas sobre el número de objetos no eliminados.
	//
	std::cout << Resource::_count << " instances of Resource leaked"
			<< std::endl;

	std::cout << GameObject::_count << " instances of GameObject leaked"
			<< std::endl;

	return 0;
}

