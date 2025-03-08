#include "Generations.h"

#include <cassert>
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

Generations::Generations()
{
}

Generations::~Generations()
{
}

void Generations::initComponent()
{
	ecs::Manager* mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void Generations::generate()
{
	RandomNumberGenerator& rand = sdlutils().rand(); // random number generator.

	// 0 -> SMALL, 1 -> MEDIUM, 2 -> BIG
	//_generationLevel = rand.nextInt(0, 3);
	_generationLevel = 2;

	int g = 10.0f + 5.0f * _generationLevel;

	_tr->setHeight(g);
	_tr->setWidth(g);

	// Además, de manera aleatoria, decide si quieres añadir uno de los componentes Follow o
	// TowardsDestination.Puedes usar imágenes distintas para cada configuración de asteroides.
}
