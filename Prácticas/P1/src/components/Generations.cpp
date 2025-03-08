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
	_generationLevel = rand.nextInt(0, 3);
	//_generationLevel = 2;

	float g = 10.0f + 5.0f * (_generationLevel + 1); // (lvl + 1) pa q no haga 0* algo

	setGenerationSize(g);
}
