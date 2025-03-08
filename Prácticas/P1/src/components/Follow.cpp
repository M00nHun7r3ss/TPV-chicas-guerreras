#include "Follow.h"

#include <cassert>
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"


Follow::Follow()
	:_tr(){
}

Follow::Follow(ecs::entity_t fighter)
	:_tr(),
	_fighter(fighter)
{
}

Follow::~Follow() {
}

void Follow::initComponent() {
	ecs::Manager* mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	_tFighter = mngr->getComponent<Transform>(_fighter);
	assert(_tr != nullptr);
}

void Follow::update() {

	_pos = _tr->getPos();
	_vel = _tr->getVel();

	_tr->getVel().set(_vel.rotate(_vel.angle(_tFighter->getPos() - _pos) > 0 ? 1.0f : -1.0f));

}

