#include "DeAcceleration.h"

#include "Transform.h"

#include <cassert>

#include "../ecs/Manager.h"

DeAcceleration::DeAcceleration(): _lessFactor(0.995f), _stopFactor(0.05f), _tr() {
}

DeAcceleration::~DeAcceleration(){
}

void DeAcceleration::initComponent(){
	ecs::Manager* mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void DeAcceleration::update(){
	Vector2D& vel = _tr->getVel();

	// Calcula la nueva velocidad decelerada.
	Vector2D deceleration = vel * _lessFactor;
	vel.set(deceleration);

	// Si alcanza valores muy peque�os para el objeto.
	if (deceleration.magnitude() <= _stopFactor) {
		vel.setX(0);
		vel.setY(0);
	}
}
