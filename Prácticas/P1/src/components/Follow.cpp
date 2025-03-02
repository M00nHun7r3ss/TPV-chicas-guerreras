#include "Follow.h"

#include <cassert>
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"


Follow::Follow()
	:_tr() {
}

Follow::Follow(Vector2D playerPos) :_tr(), _playerPos(playerPos)
{
}

Follow::~Follow() {
}

void Follow::initComponent() {
	ecs::Manager* mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void Follow::update() {
	_vel.rotate(_vel.angle(_playerPos - _tr->getPos()) > 0 ? 1.0f : -1.0f);
	_tr->getVel().set(_vel);
}

