// This file is part of the course TPV2@UCM - Samir Genaim

#include "WalkingState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "NinjaWS.h"

WalkingState::WalkingState() :
		_speed() {
}

WalkingState::~WalkingState() {
}

void WalkingState::enter(NinjaWS &o) {
	o.setImg(&sdlutils().images().at("ninja_walking"));
	_speed = 0.0f;
}

void WalkingState::handleInput(NinjaWS &o) {
	auto &ihdlr = ih();
	if (ihdlr.isKeyDown(SDLK_RIGHT)) {
		_speed = 5.0f;
	} else if (ihdlr.isKeyDown(SDLK_LEFT)) {
		_speed = -5.0f;
	} else {
		o.setState(NinjaWS::STANDING);
	}

}

void WalkingState::update(NinjaWS &o) {
	auto &pos = o.getPos();
	pos.setX(pos.getX() + _speed);
}
