// This file is part of the course TPV2@UCM - Samir Genaim

#include "JumpingState.h"

#include "../sdlutils/SDLUtils.h"
#include "NinjaWS.h"
JumpingState::JumpingState() :
		_speed() {

}

JumpingState::~JumpingState() {
}

void JumpingState::enter(NinjaWS &o) {
	o.setImg(&sdlutils().images().at("ninja_jumping"));
	_speed = -10.0;
}

void JumpingState::handleInput(NinjaWS &o) {
}

void JumpingState::update(NinjaWS &o) {
	auto &pos = o.getPos();

	pos.setY(pos.getY() + _speed);
	if (_speed < 0) {
		_speed *= 0.9;
		if (_speed > -1.0f) {
			_speed = 10.0f;
		}
	} else {
		_speed *= 1.1f;
		if (pos.getY() + o.getHeight() > sdlutils().height()) {
			pos.setY(sdlutils().height() - o.getHeight());
			o.setState(NinjaWS::STANDING);
		}
	}
}
