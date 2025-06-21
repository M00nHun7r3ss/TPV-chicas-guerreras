#include "StillState.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "PacmanWS.h"


void StillState::enter(PacmanWS& o)
{
	o.setImageRect(&sdlutils().images().at("sprites"), 8, 8, 0, 1);
}

void StillState::handleInput(PacmanWS& o)
{
	auto& ihdlr = ih();
	if (ihdlr.isKeyDown(SDL_SCANCODE_UP))
	{
		o.setState(PacmanWS::WALKING);
		_vel = Vector2D(0, -2.0f).rotate(_rot);
	}
	else if (ihdlr.isKeyDown(SDL_SCANCODE_LEFT)
		|| ihdlr.isKeyDown(SDL_SCANCODE_RIGHT))
	{
		o.setState(PacmanWS::SPINNING);
	}

}

void StillState::update(PacmanWS& o)
{

}
