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
	//Anadimos el componente de fruta milagrosa

	std::vector<ecs::entity_t> fruits = _mngr->getEntities(ecs::grp::FRUITS);
	for (int i = 0; i < fruits.size(); i++)
	{
		// si lo tiene
		if (_mngr->hasComponent<MiraculousComponent>(fruits[i]))
		{
			// lo coge.
			MiraculousComponent* mc = _mngr->getComponent<MiraculousComponent>(fruits[i]);
			std::string sprite;


			VirtualTimer& vt = sdlutils().virtualTimer();
			Uint32 _timeBetweenEachSpawn;

			// si es miraculous...
			if (mc->_isMiraculous)
			{
				sprite = "tennis_ball";

				_timeBetweenEachSpawn = mc->_M * 1000;

				//Pasado ese tiempo
				if (vt.currTime() > _timeBetweenEachSpawn + _lastFruitChanged) {
					_lastFruitChanged = vt.currTime();
					mc->_isMiraculous = false;
					mc->_N = _rand.nextInt(1, 6); //cambiar por 10 y 21
				}
			}
			else // si no lo es...
			{
				sprite = "star";

				_timeBetweenEachSpawn = mc->_N * 1000;

				//Pasado ese tiempo
				if (vt.currTime() > _timeBetweenEachSpawn + _lastFruitChanged) {
					_lastFruitChanged = vt.currTime();
					mc->_isMiraculous = true;
					mc->_M = _rand.nextInt(1, 6);
				}
			}

			std::cout << "N: " << mc->_N << std::endl;
			std::cout << "M: " << mc->_M << std::endl;
			std::cout << "Mirac: " << mc->_isMiraculous << std::endl;

			_mngr->addComponent<Image>(fruits[i], &sdlutils().images().at(sprite));
		}
	}
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
				_mngr->addComponent<MiraculousComponent>(e, 0, 0);
				
			}
	        else { _mngr->addComponent<Image>(e, &sdlutils().images().at("star")); }

            tr->init(Vector2D((i*100)+20, (j * 100) + 20), Vector2D(), size, size, 0.0f);
        }
    }
}

void FoodSystem::timeCounter(float& s)
{
	
}
