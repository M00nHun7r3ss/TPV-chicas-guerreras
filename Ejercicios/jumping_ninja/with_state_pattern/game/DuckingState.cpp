// This file is part of the course TPV2@UCM - Samir Genaim

#include "DuckingState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "NinjaWS.h"
DuckingState::DuckingState() :
		_charge() {
}

DuckingState::~DuckingState() {
}

void DuckingState::enter(NinjaWS &o) {
	o.setImg(&sdlutils().images().at("ninja_ducking"));
	_charge = 0.0f;
}

void DuckingState::handleInput(NinjaWS &o) {
	auto &ihdlr = ih();
	if (ihdlr.isKeyDown(SDLK_DOWN)) {
		_charge += 0.01f;
		if (_charge > 1.0f) {
			o.setState(NinjaWS::ATTACKING);
		}
	} else {
		o.setState(NinjaWS::STANDING);
	}
}

void DuckingState::update(NinjaWS &o) {
}
