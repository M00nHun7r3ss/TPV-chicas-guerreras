#include "Health.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

Health::Health() : _currentHealth(3), _maxHealth(3), _tr() {
}

Health::~Health(){
}

void Health::initComponent(){
	/*auto* mngr = _ent->getMngr();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);*/
}

void Health::render() {
	
	SDL_Rect heart = { 5, 5, 20, 20 };
	for (int i = 0; i < _currentHealth; i++)
	{
		heart.x = (i * 20) + 5;
	}
		
	/*auto& sdl = *SDLUtils::Instance();
	std::vector<Texture&> hearts;
	auto& heart = sdl.images().at("heart"); // corazón.
	for (int i = 0; i < _maxHealth; i++){
		hearts.emplace_back(heart);
	}

	sdl.clearRenderer();
	for (int i = 0; i < _currentHealth; i++)
	{
		hearts[i].render(10 * i, 10);
	}*/
}

void Health::update()
{
	auto& ihldr = ih();

	if (ihldr.keyDownEvent()){
		if (ihldr.isKeyDown(SDLK_e)) // Damage - E
		{
			damage();
		}
		else if (ihldr.isKeyDown(SDLK_h)) // Heal - H
		{
			heal();
		}
	}
	
}

void Health::damage()
{
	_currentHealth--;
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
