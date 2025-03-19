#include "Health.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

Health::Health()
	: _currentHealth(3),
	_maxHealth(3),
	_tex(SDLUtils::Instance()->images().at("heart")) {
}

Health::~Health() {
}

void Health::damage(int n)
{
	_currentHealth += n;
	sdlutils().soundEffects().at("damage").play(0, 1);
}

void Health::heal()
{
	_currentHealth = _maxHealth;
}