// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameObject.h"

#include "Game.h"

int GameObject::_count = 0;

GameObject::GameObject(Resource *r) :
		_alive(true), _r(r), _x(), _y() {

	_count++;
}

GameObject::~GameObject() {
	_count--;
}

void GameObject::update() {

	// mover el objeto
	_x += _r->action() % 2;
	_y += _r->action() % 2;

	// morir?
	if (_r->action() % 10 < 3) {
		_alive = false; // marcar la entidad como muerta
	} else {
		// clonar?
		unsigned int n = _r->action() % 10;
		if (n < 3) {
			// Añadir una entidad que con un recuso nuevo
			Game::Instance()->add(new GameObject(new Resource()));
		} else if (n < 5) {
			// Añadir una entidad que comparte el recurso
			Game::Instance()->add(new GameObject(_r));
		}
	}
}

bool GameObject::isAlive() {
	return _alive;
}

