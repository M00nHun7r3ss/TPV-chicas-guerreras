#include "FoodSystem.h"

#include <algorithm>

#include "PacManSystem.h"
#include "../components/Health.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

FoodSystem::FoodSystem()
{
}

FoodSystem::~FoodSystem(){
}

void FoodSystem::initSystem(){
}

void FoodSystem::generateFruitGrid()
{
	// Always use the random number generator provided by SDLUtils
	RandomNumberGenerator& rand = sdlutils().rand();

	for (unsigned i = 0u; i < _ghostLimit; i++) {

		// add an entity to the manager
		ecs::entity_t e = _mngr->addEntity(ecs::grp::GHOSTS);

		// add a Transform component
		Transform* tr = _mngr->addComponent<Transform>(e);

		int size = 30;

		//Esquina por el que sale
		//0 - arriba/izqd, 1 - abajo/izqd, 2 - abajo/dcha, 3 - arriba/dcha
		int esquina = rand.nextInt(0, 4); //Hasta max + 1, como el Rnd.Next de C#
		int x, y;
		switch (esquina) //Esto es asi porque el origen del sprite es arriba izquierda 
		{
		case 0: //arriba/izqd
			x = 0;
			y = 0;
			break;
		case 1: //abajo/izqd,
			x = 0;
			y = sdlutils().height() - size;
			break;
		case 2: //abajo/dcha
			x = sdlutils().width() - size;
			y = sdlutils().height() - size;
			break;
		case 3: //arriba/dcha
			x = sdlutils().width() - size;
			y = 0;
			break;
		default:
			break;
		}

		//Inicializa transform
		tr->init(Vector2D(x, y), Vector2D(), size, size, 0.0f);

		// add an Image Component
		_mngr->addComponent<Image>(e, &sdlutils().images().at("star"));

		_currNumOfGhosts++;
	}
}
