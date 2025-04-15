#include "FoodSystem.h"

#include <algorithm>

#include "PacManSystem.h"
#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../components/MiraculousComponent.h"
#include "../ecs/Manager.h"


FoodSystem::FoodSystem()
	: _currNumOfFruit(0),
	  _fruitType(false),
      _rand(sdlutils().rand()),
	  _lastFruitChanged(0)
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
			int col, row;

			VirtualTimer& vt = sdlutils().virtualTimer();
			Uint32 _timeBetweenEachSpawn;

			// fil cols general para renderizar
			col = 4;
			row = 1;

			// si no es miraculous...
			if (!mc->_isMiraculous)
			{
				// fil cols de normal (cereza).
				col = 4;
				row = 1;

				_timeBetweenEachSpawn = mc->_N * 1000;

				//Pasado ese tiempo
				if (vt.currRealTime() > _timeBetweenEachSpawn + _lastFruitChanged) {
					_lastFruitChanged = vt.currRealTime();
					mc->_isMiraculous = true;
					mc->_M = _rand.nextInt(1, 6);
				}
			}
			else // si lo es...
			{
				// fil cols de milagrosa (pera).
				col = 7;
				row = 1;

				_timeBetweenEachSpawn = mc->_M * 1000;

				//Pasado ese tiempo
				if (vt.currRealTime() > _timeBetweenEachSpawn + _lastFruitChanged) {
					_lastFruitChanged = vt.currRealTime();
					mc->_isMiraculous = false;
					mc->_N = _rand.nextInt(10, 21); //cambiar por 10 y 21
				}
			}

			_mngr->addComponent<ImageWithFrames>(fruits[i], &sdlutils().images().at("sprites"), col, row);
		}
	}

	//Comprobamos si hemos llegado al final de juego
	checkNoFruit();
}

void FoodSystem::recieve(const Message& m)
{
	//No reseteamos aqui el vt, porque lo hacemos en el pacman
	switch (m.id)
	{
	case _m_NEW_GAME: // PONER NEW GAME
        generateFruitGrid();
		//Reseteamos el contador de tiempo
		_lastFruitChanged = 0;
        break;
	case _m_ROUND_START:
		//Reseteamos el contador de tiempo
		_lastFruitChanged = 0;
		break;
	case _m_PACMAN_FOOD_COLLISION:
		deleteFruit(m.pacman_food_collision_data.f);
		break;

	default:
		break;
	}
}

void FoodSystem::generateFruitGrid()
{
    //tamano
    int size = 50;

    for (unsigned i = 0u; i < MAX_FRUIT_NUMBER/5; i++) {
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
				// lo cogemos
				MiraculousComponent* mc = _mngr->getComponent<MiraculousComponent>(e);
				//Inicialmente sera normal
				mc->_isMiraculous = false;
				
			}
	        else { _mngr->addComponent<ImageWithFrames>(e, &sdlutils().images().at("sprites"), 4, 1); }

            tr->init(Vector2D((i*100)+20, (j * 100) + 20), Vector2D(), size, size, 0.0f);
        }
    }
}

void FoodSystem::deleteFruit(ecs::entity_t e)
{
	_mngr->setAlive(e, false);
	_currNumOfFruit--;

	// play sound on channel 1 (if there is something playing there
	// it will be cancelled
	// TODO: VOLVER A ACTIVAR AL FINAL
	//sdlutils().soundEffects().at("pacman_eat").play(0, 1);

}

void FoodSystem::checkNoFruit()
{
	if (_currNumOfFruit == 0)
	{
		//Envia mensaje de que ha acabado el juego
		Message m;
		m.id = _m_ROUND_START;
		Game::Instance()->getManager()->send(m);

		// !!! cambia a GameOverState (FINAL BUENO)
		Game::Instance()->setState(Game::GAMEOVER);
	}
}
