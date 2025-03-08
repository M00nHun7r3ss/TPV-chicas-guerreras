#include "Health.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

Health::Health()
	: _currentHealth(3),
	  _maxHealth(3),
	  _tr(),
	  _tex(SDLUtils::Instance()->images().at("heart")) {
}

Health::~Health(){
}

void Health::render() {

	SDL_Rect dest = { 5, 10, 40, 40 };

	// vamos modificando la x y renderizando para que vayan en fila.
	for (int i = 0; i < _currentHealth; i++){

		_tex.render(dest);
		dest.x = dest.x + 45;
	}
}

void Health::update()
{
	auto& ihldr = ih();

	if (ihldr.keyDownEvent()){
		if (ihldr.isKeyDown(SDLK_e)) // Damage - E
		{
			damage(-1);
		}
		else if (ihldr.isKeyDown(SDLK_h)) // Heal - H
		{
			heal();
		}
	}

	
}

void Health::damage(int n)
{
	_currentHealth += n;
	if (_currentHealth <= 0) {
		//Muerto
		std::cout << "Muerto" << std::endl;
	}
}

void Health::heal()
{
	_currentHealth = _maxHealth;
	//Curado
	std::cout << "Curado" << std::endl;
}
