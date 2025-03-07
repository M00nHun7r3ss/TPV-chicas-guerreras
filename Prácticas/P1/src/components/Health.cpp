#include "Health.h"

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

Health::Health() : _currentHealth(3), _maxHealth(3), _tr() {
}

Health::~Health(){
}

void Health::render() {
	// ---- ¡¡¡¡ PASOS PARA RENDERIZAR !!!! ----.
	
	// reference to the SDLUtils Singleton.
	auto& sdl = *SDLUtils::Instance();

	// store the 'renderer' in a local variable, just for convenience
	SDL_Renderer* renderer = sdl.renderer();
	
	// heart image.
	auto& heart = sdl.images().at("heart"); 

	// Creamos el rectángulo con el tamaño y la posicion inicial.
	SDL_Rect heartRect;
	heartRect.x = 5;
	heartRect.y = 10;
	// por darle un tamaño....
	heartRect.w = 40;
	heartRect.h = 40;

	// vamos modificando la x y renderizando para que vayan en fila.
	for (int i = 0; i < _currentHealth; i++){
		heart.render(heartRect);
		heartRect.x = heartRect.x + 45;
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
	_currentHealth + n;
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
