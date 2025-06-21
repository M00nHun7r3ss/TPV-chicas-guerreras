#include "SpinningState.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "PacmanWS.h"


void SpinningState::enter(PacmanWS& o)
{
	o.setImageRect(&sdlutils().images().at("sprites"), 8, 8, 2, 1);
}

void SpinningState::handleInput(PacmanWS& o)
{
	auto& ihdlr = ih();
	if (ihdlr.isKeyDown(SDL_SCANCODE_LEFT)) {
		_deg = -5.0f;
	}
	else if (ihdlr.isKeyDown(SDL_SCANCODE_RIGHT)) {
		_deg = 5.0f;
	}
	else if (ihdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
		o.setState(PacmanWS::STILL);
	}
}

void SpinningState::update(PacmanWS& o)
{
	_rot += _deg;
}
