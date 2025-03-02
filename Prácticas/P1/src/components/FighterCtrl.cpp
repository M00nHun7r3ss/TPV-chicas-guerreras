#include "FighterCtrl.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
#include "Transform.h"

FighterCtrl::FighterCtrl() : _tr(nullptr)
{
}

FighterCtrl::~FighterCtrl()
{
}

void FighterCtrl::initComponent()
{
	ecs::Manager* mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void FighterCtrl::update()
{
	InputHandler &ihldr = ih();

	Vector2D& vel_ = _tr->getVel();
	float rot = _tr->getRot();

	float thrust = 0.2f;
	float speedLimit = 3.0f;

	if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
		_tr->setRot(rot + 5.0f);
	}
	else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
		_tr->setRot(rot - 5.0f);
	}
	else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed

		Vector2D newVel = vel_ + Vector2D(0, -1).rotate(rot) * thrust;
		if (newVel.magnitude() > speedLimit) {
			newVel = newVel.normalize() * speedLimit;
		}
		vel_.set(newVel);

		//Efecto de sonido, pendiente de que lo suba Samir
		/*// play sound on channel 1 (if there is something playing there
		// it will be cancelled
		sdlutils().soundEffects().at("thrust").play(0, 1);*/
	}
}

