#include "WalkingState.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "PacmanWS.h"


void WalkingState::enter(PacmanWS& o)
{
	o.setImageRect(&sdlutils().images().at("sprites"), 8, 8, 1, 1);
}

void WalkingState::handleInput(PacmanWS& o)
{
	auto& ihdlr = ih();
	if (ihdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
		o.setState(PacmanWS::STILL);
	}
}

void WalkingState::update(PacmanWS& o)
{
	Vector2D p = o.getPos();
	o.getPos().set(o.getPos() + o.getVel());

	if (o.getPos().getY() < 0 || o.getPos().getY() + o.getHeight() > sdlutils().height()
		|| o.getPos().getX() < 0
		|| o.getPos().getX() + o.getWidth() > sdlutils().width()) {
		std::cout << "ff" << std::endl;
		o.getPos().set(p);
		o.getVel().set(0.0f, 0.0f);
		o.setImageRect(&sdlutils().images().at("sprites"), 8, 8, 0, 1);
	}
	o.getPos().set(o.getPos());
}
