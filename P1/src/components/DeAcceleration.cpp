#include "DeAcceleration.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

DeAcceleration::DeAcceleration(): _lessFactor(0.995f), _stopFactor(0.05f), _tr() {
}

DeAcceleration::~DeAcceleration(){
}

void DeAcceleration::initComponent(){
	auto* mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void DeAcceleration::update(){
	auto& vel = _tr->getVel();

	// Calcula la nueva velocidad decelerada.
	Vector2D deceleration = vel * _lessFactor;
	vel.set(deceleration);

	// Si alcanza valores muy pequeños para el objeto.
	if (deceleration.magnitude() <= _stopFactor) {
		vel.setX(0);
		vel.setY(0);
	}
	
}
