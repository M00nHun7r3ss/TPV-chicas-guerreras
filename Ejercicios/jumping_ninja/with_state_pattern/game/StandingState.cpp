// This file is part of the course TPV2@UCM - Samir Genaim

#include "StandingState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "NinjaWS.h"
StandingState::StandingState() {

}

StandingState::~StandingState() {
}

void StandingState::enter(NinjaWS &o) {
	o.setImg(&sdlutils().images().at("ninja_standing"));
}

void StandingState::handleInput(NinjaWS &o) {
	auto &ihdlr = ih();
	if (ihdlr.isKeyDown(SDLK_RIGHT) || ihdlr.isKeyDown(SDLK_LEFT)) {
		o.setState(NinjaWS::WALKING);
	} else if (ihdlr.isKeyDown(SDLK_UP)) {
		o.setState(NinjaWS::JUMPING);
	} else if (ihdlr.isKeyDown(SDLK_DOWN)) {
		o.setState(NinjaWS::DUCKING);
	}
}

void StandingState::update(NinjaWS &o) {
}
