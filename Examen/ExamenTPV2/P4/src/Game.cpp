// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"
#include "GameObject.h"
#include "Resource.h"

Game::Game() {
}

Game::~Game() {
	for (GameObject *o : _v) {
		delete o;
	}
}

bool Game::init() {
	for (int i = 0; i < 10; i++) {
		add(new GameObject(new Resource()));
	}
	return true;
}

void Game::start(unsigned int n) {

	// EL BUCLE DEL "JUEGO"
	while (n > 0) {

		// actualizar las entidades
		std::size_t vsize = _v.size();
		for (std::size_t i = 0u; i < vsize; i++) {
			_v[i]->update();
		}

		/*
		// actualizar la entidades: bucle alternativo usando for-each
		for (GameObject* o : _v) {
			o->update();
		}
		*/

		// borrar las entidades muertas
		refresh();
		n--;
	}
}

void Game::refresh() {
	
	// borrar entidades muertas
	_v.erase(std::remove_if(_v.begin(), _v.end(), [](GameObject* a) {
		if (!a->isAlive()) {
			delete a;
			return true;
		}
		else {
			return false;
		}
		}), _v.end());

}

void Game::add(GameObject *e) {
	_v.push_back(e);
}
