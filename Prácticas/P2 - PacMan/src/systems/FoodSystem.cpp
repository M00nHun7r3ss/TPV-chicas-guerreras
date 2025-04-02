#include "FoodSystem.h"

#include <algorithm>

#include "PacManSystem.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

FoodSystem::FoodSystem() : _currNumOfFruit(0), _lastFruitAdded(0), _fruitType(false)
{
}

FoodSystem::~FoodSystem() {
}

void FoodSystem::initSystem() {
}

void FoodSystem::update()
{

}

void FoodSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_ROUND_START: // PONER NEW GAME
        generateFruitGrid();
        break;

	default:
		break;
	}
}

void FoodSystem::generateFruitGrid()
{
    //posicion
    int x = 50,
        y = 50;
    //tamano
    int size = 50;

    for (unsigned i = 0u; i < MAX_FRUIT_NUMBER; i++) {

        // add an entity to the manager
        ecs::entity_t e = _mngr->addEntity(ecs::grp::FRUITS);

        // add a Transform component
        Transform* tr = _mngr->addComponent<Transform>(e);
        //tr->_pos.setX(x);
        tr->_pos.setY(y);

        //std::cout << "Fruit " << i << " x1:" << tr->_pos.getX() << " y1:" << tr->_pos.getY() << std::endl;

		//inicializa la posicion
    	//Cada fila tiene 8 frutas
        for (int j = 0; j < MAX_FRUIT_NUMBER / 5; j++) 
        {
            // vamos modificando la x y renderizando para que vayan en diferentes columnas
            tr->_pos.setX(tr->_pos.getX() + x);

            // add an Image Component segun milagroso o no
            if (_fruitType) { _mngr->addComponent<Image>(e, &sdlutils().images().at("tennis_ball")); }
            else { _mngr->addComponent<Image>(e, &sdlutils().images().at("star")); }

            _currNumOfFruit++;
        }

        //std::cout << "Fruit " << i << " x2:" << tr->_pos.getX() << " y2:" << tr->_pos.getY() << std::endl;
        //Inicializa transform
        tr->init(Vector2D(x, y), Vector2D(), size, size, 0.0f);

        // vamos modificando la y renderizando para que vayan en diferentes filas
        tr->_pos.setY(tr->_pos.getY() + y);
        //Reseteamos el valor x 
        tr->_pos.setX(x);

        //std::cout << "Fruit " << i << " x3:" << tr->_pos.getX() << " y3:" << tr->_pos.getY() << std::endl;

    }
}
