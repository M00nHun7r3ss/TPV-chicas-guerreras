#include "FoodSystem.h"

#include <algorithm>

#include "PacManSystem.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/MiraculousComponent.h"
#include "../ecs/Manager.h"


FoodSystem::FoodSystem()
	: _currNumOfFruit(0),
	  _fruitType(false),
      _rand(sdlutils().rand())
{
}

FoodSystem::~FoodSystem() {
}

void FoodSystem::initSystem() {
}

void FoodSystem::update()
{
	//VirtualTimer& vt = sdlutils().virtualTimer();

	////Si es milagrosa
	//if (_fruitType)
	//{
	//	//La fruta será normal un N random entre 10 y 20 s
	//	int tiempo = _rand.nextInt(1, 6); //cambiar por 10 y 21
	//	Uint32 _timeBetweenEachSpawn = tiempo * 1000;

	//	//Pasado ese tiempo
	//	if (vt.currTime() > _timeBetweenEachSpawn + _lastFruitChanged) {
	//		//La fruta vuelve a ser milagrosa
	//		_isMiraculous = true;
	//		_lastFruitChanged = vt.currTime();
	//	}
	//	//La fruta será milagrosa un M random entre 1 y 5 s
	//	tiempo = _rand.nextInt(1, 6);
	//	_timeBetweenEachSpawn = tiempo * 1000;

	//	//Pasado ese tiempo
	//	if (vt.currTime() > _timeBetweenEachSpawn + _lastFruitChanged) {
	//		//La fruta vuelve a ser normal
	//		_isMiraculous = false;
	//		_lastFruitChanged = vt.currTime();
	//	}
	//}
}

void FoodSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_NEW_GAME: // PONER NEW GAME
        generateFruitGrid();
        break;

	default:
		break;
	}
}

void FoodSystem::generateFruitGrid()
{
    //tamano
    int size = 50;

    for (unsigned i = 0u; i <= MAX_FRUIT_NUMBER/5; i++) {
        for (unsigned j = 0u; j <= MAX_FRUIT_NUMBER/8; j++)
        {
	        // add an entity to the manager
	        ecs::entity_t e = _mngr->addEntity(ecs::grp::FRUITS);
			_currNumOfFruit++;

        	// add a Transform component
	        Transform* tr = _mngr->addComponent<Transform>(e);
	        
	        // add an Image Component segun milagroso o no
			int prob = _rand.nextInt(1, 11); // [1, 11).

			if (prob == 1) _fruitType = true; // milagroso.
			else _fruitType = false; // no milagroso.

	        if (_fruitType) 
			{ 
				//Anadimos el componente de fruta milagrosa
				_mngr->addComponent<MiraculousComponent>(e);
				_mngr->addComponent<Image>(e, &sdlutils().images().at("tennis_ball"));
			}
	        else { _mngr->addComponent<Image>(e, &sdlutils().images().at("star")); }

            tr->init(Vector2D((i*100)+20, (j * 100) + 20), Vector2D(), size, size, 0.0f);
        }
    }
}
