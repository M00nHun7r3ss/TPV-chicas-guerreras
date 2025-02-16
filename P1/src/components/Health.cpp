#include "Health.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
//#include "GameState.h"

Health::Health() : _currentHealth(3), _maxHealth(3) {
}

Health::~Health(){
}

void Health::initComponent(){
	/*auto mngr = _ent->getMngr();
	_gameState = mngr->getComponent<GameState>(_ent);
	assert(_gameState != nullptr);*/
}

void Health::render(){
}

void Health::update()
{
	auto& ihldr = ih();

	if (ihldr.keyDownEvent())
	{
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
