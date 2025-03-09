#include "Health.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

Health::Health()
	: _currentHealth(3),
	  _maxHealth(3),
	  _tex(SDLUtils::Instance()->images().at("heart")) {
}

Health::~Health(){
}

void Health::render() {

	// pos arriba izquierda.
	SDL_Rect dest = { 5, 10, 40, 40 };

	// vamos modificando la x y renderizando para que vayan en fila.
	for (int i = 0; i < _currentHealth; i++){
		assert(&_tex != nullptr);
		_tex.render(dest);
		dest.x = dest.x + 45;
	}
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
