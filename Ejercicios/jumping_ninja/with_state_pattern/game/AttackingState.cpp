// This file is part of the course TPV2@UCM - Samir Genaim

#include "AttackingState.h"

#include "../sdlutils/SDLUtils.h"
#include "NinjaWS.h"
AttackingState::AttackingState() :
		_speed() {
	// TODO Auto-generated constructor stub

}

AttackingState::~AttackingState() {
}

void AttackingState::enter(NinjaWS &o) {
	o.setImg(&sdlutils().images().at("ninja_attacking"));
	_speed = -10.0f;
}

void AttackingState::handleInput(NinjaWS &o) {
}

void AttackingState::update(NinjaWS &o) {
	auto &_pos = o.getPos();
	_pos.setY(_pos.getY() + _speed);
	_pos.setX(_pos.getX() + 5.0f);
	if (_speed < 0) {
		_speed *= 0.9;
		if (_speed > -1.0f) {
			_speed = 10.0f;
		}
	} else {
		_speed *= 1.1f;
		if (_pos.getY() + o.getHeight() > sdlutils().height()) {
			_pos.setY(sdlutils().height() - o.getHeight());
			o.setState(NinjaWS::STANDING);
		}
	}
}
