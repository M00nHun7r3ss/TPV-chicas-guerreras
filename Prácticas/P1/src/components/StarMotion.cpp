// This file is part of the course TPV2@UCM - Samir Genaim

#include "StarMotion.h"

#include <cassert>
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrl.h"
#include "Transform.h"


StarMotion::StarMotion() :
		_tr(), _lastUpdate() {
}

StarMotion::~StarMotion() {
}

void StarMotion::initComponent() {
	ecs::Manager *mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);

	_lastUpdate = sdlutils().virtualTimer().currTime();
}

void StarMotion::update() {

	//// update every 50ms
	//if (_lastUpdate + 50 > sdlutils().virtualTimer().currTime())
	//	return;

	//_lastUpdate = sdlutils().virtualTimer().currTime();

	//pos = pos + vel
	_tr->getPos().set(_tr->getPos() + _tr->getVel());

	//_tr->setWidth(_tr->getWidth() * 0.95f);
	//_tr->setHeight(_tr->getHeight() * 0.95f);

	//if (_tr->getWidth() < 5 || _tr->getHeight() < 5) {
	//	auto *mngr = _ent->getMngr();
	//	mngr->setAlive(_ent, false);
	//	auto ginfo = mngr->getHandler(ecs::hdlr::GAMEINFO);
	//	mngr->getComponent<GameCtrl>(ginfo)->onAsteroidDissappeared();
	//} else {
	//	_tr->setRot(_tr->getRot() + 5.0f);
	//}
}
