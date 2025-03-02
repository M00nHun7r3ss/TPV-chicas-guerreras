// This file is part of the course TPV2@UCM - Samir Genaim

#include "AsteroidMotion.h"

#include <cassert>
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrl.h"
#include "Transform.h"


AsteroidMotion::AsteroidMotion() :
		_tr(), _lastUpdate() {
}

AsteroidMotion::~AsteroidMotion() {
}

void AsteroidMotion::initComponent() {
	ecs::Manager *mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);

	_lastUpdate = sdlutils().virtualTimer().currTime();
}

void AsteroidMotion::update(){
	//pos = pos + vel
	_tr->getPos().set(_tr->getPos() + _tr->getVel());
}
