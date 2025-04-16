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
		ImageWithFrames* iwf = _mngr->getComponent<ImageWithFrames>(fruits[i]);
		// si lo tiene
		if (_mngr->hasComponent<MiraculousComponent>(fruits[i]))
		{
			// lo sustrae.
			MiraculousComponent* mc = _mngr->getComponent<MiraculousComponent>(fruits[i]);

			VirtualTimer& vt = sdlutils().virtualTimer();
			Uint32 _timeBetweenEachSpawn;

			// si no es miraculous...
			if (!mc->_isMiraculous)
			{
				// fil cols de normal (cereza).
				iwf->setColRow(4, iwf->getRow());

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
				iwf->setColRow(7, iwf->getRow());

				_timeBetweenEachSpawn = mc->_M * 1000;

				//Pasado ese tiempo
				if (vt.currRealTime() > _timeBetweenEachSpawn + _lastFruitChanged) {
					_lastFruitChanged = vt.currRealTime();
					mc->_isMiraculous = false;
					mc->_N = _rand.nextInt(10, 21); //cambiar por 10 y 21
				}
			}

			
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
    int size = 30;

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

			// inicialmente cereza.
			_mngr->addComponent<ImageWithFrames>(e, &sdlutils().images().at("sprites"), 4, 1);

            tr->init(Vector2D((i*100)+30, (j * 100) + 30), Vector2D(), size, size, 0.0f);
        }
    }
}

void FoodSystem::deleteFruit(ecs::entity_t e)
{
	_mngr->setAlive(e, false);
	_currNumOfFruit--;

	// play sound on channel 1 (if there is something playing there
	// it will be cancelled
	//TODO: DESCOMENTAR
	//sdlutils().soundEffects().at("pacman_eat").play(0, 1);

}

void FoodSystem::checkNoFruit()
{
	if (_currNumOfFruit == 0)
	{
		//Sonido de ganar
		//TODO: DESCOMENTAR
		//sdlutils().soundEffects().at("pacman_won").play(0, 1);

		//Envia mensaje de que ha acabado el juego
		Message m;
		m.id = _m_ROUND_START;
		Game::Instance()->getManager()->send(m);

		// !!! cambia a GameOverState (FINAL BUENO)
		Game::Instance()->setState(Game::GAMEOVER);
	}
}
