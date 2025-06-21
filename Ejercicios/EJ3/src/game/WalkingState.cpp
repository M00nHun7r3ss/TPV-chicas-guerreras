#include "WalkingState.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "PacmanWS.h"


void WalkingState::enter(PacmanWS& o)
{
}

void WalkingState::handleInput(PacmanWS& o)
{
	auto& ihdlr = ih();
	if (ihdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
		o.setState(PacmanWS::STILL);
		o.setImageRect(&sdlutils().images().at("sprites"), 8, 8, 0, 1);
	}
}

void WalkingState::update(PacmanWS& o)
{
	_pos = _pos + _vel;

	auto p = _pos;
	if (_pos.getY() < 0 || _pos.getY() + _height > sdlutils().height()
		|| _pos.getX() < 0
		|| _pos.getX() + _width > sdlutils().width()) {
		std::cout << "ff" << std::endl;
		_pos.set(p);
		_vel.set(0.0f, 0.0f);
		o.setImageRect(&sdlutils().images().at("sprites"), 8, 8, 0, 1);
	}
}
