#include "AsteroidsUtils.h"

#include <algorithm>
#include <vector>
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"


AsteroidsUtils::AsteroidsUtils()
	: _centroVent((float)(sdlutils().width() / 2), (float)(sdlutils().height() / 2)),
	  _mngr(Game::Instance()->getManager()){
}

void AsteroidsUtils::create_asteroids(int n)
{
	for (int i = 0; i < n; i++){
		// Always use the random number generator provided by SDLUtils
		RandomNumberGenerator& rand = sdlutils().rand();

		// add and entity to the manager
		ecs::entity_t e = _mngr->addEntity(ecs::grp::ASTEROIDS);

		// add a Transform component, and initialise it with random size and position
		Transform* tr = _mngr->addComponent < Transform >(e);

		// --- POS ALEATORIA ---
		int size = 50;
		//Lado por el que sale
		//0 - arriba, 1 - abajo, 2 - izqd, 3 - dcha
		int lado = rand.nextInt(0, 4); //Hasta max + 1, como el Rnd.Next de C#
		int x, y;
		switch (lado) //Esto es asi porque el origen del sprite es arriba izquierda 
		{
		case 0: //Arriba
			x = rand.nextInt(0, sdlutils().width() - size);
			y = rand.nextInt(0, size);
			break;
		case 1: //Abajo
			x = rand.nextInt(0, sdlutils().width() - size);
			y = rand.nextInt(sdlutils().height() - 2 * size, sdlutils().height() - size);
			break;
		case 2: //Izquierda
			x = rand.nextInt(0, size);
			y = rand.nextInt(0, sdlutils().height() - size);
			break;
		case 3: //Derecha
			x = rand.nextInt(sdlutils().width() - 2 * size, sdlutils().width() - size);
			y = rand.nextInt(0, sdlutils().height() - size);
			break;
		default:
			break;
		}

		// --- VELOCIDAD ALEATORIA ---
		//Centro ventana para que los asteroides vayan hacia el centro
		int rx = rand.nextInt(-100, 101);
		int ry = rand.nextInt(-100, 101);
		Vector2D centro = { _centroVent.getX() + rx, _centroVent.getY() + ry };

		float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
		Vector2D v = (centro - Vector2D(x, y)).normalize() * speed;

		// inicializa el asteroide en ese transform
		tr->init(Vector2D(x, y), v, size, size, 0.0f);

		// Los demas componentes
		_mngr->addComponent<Image>(e, &sdlutils().images().at("star")); // add an Image Componet (cambiar luego).
		_mngr->addComponent<ShowAtOppositeSide>(e); // add ShowAtOppositeSide Component.


		//mngr->getComponent<Transform>(mngr->setHandler(ecs::hdlr::FIGHTER, fighter))
		//mngr->addComponent<Follow>(e, mngr->getComponent<Transform>(mngr->setHandler(ecs::hdlr::FIGHTER, fighter)));

		// _currNumOfAsteroids++;
	}
}

void AsteroidsUtils::create_splitted_asteroids(ecs::entity_t* a)
{
	for (int i = 0; i < 2; i++) {

		// add and entity to the manager
		ecs::entity_t e = _mngr->addEntity(ecs::grp::ASTEROIDS);

		// add a Transform component, and initialise it with random size and position
		Transform* tr = _mngr->addComponent < Transform >(e);

		// --- VELOCIDAD Y POSICION---
		Transform* aTf = _mngr->getComponent<Transform>(*a);

		float size = aTf->getHeight() / 2; // la mitad q el padre.

		int r = sdlutils().rand().nextInt(0, 360);
		Vector2D pos = aTf->getPos() + aTf->getVel().rotate(r) * 2 * std::max(size, size);
		Vector2D vel = aTf->getVel().rotate(r) * 1.1f;
	
		// inicializa el asteroide en ese transform
		tr->init(pos, vel, size, size, r);

		// Los demas componentes
		_mngr->addComponent<Image>(e, &sdlutils().images().at("star")); // add an Image Componet (cambiar luego).
		_mngr->addComponent<ShowAtOppositeSide>(e); // add ShowAtOppositeSide Component.

		//mngr->getComponent<Transform>(mngr->setHandler(ecs::hdlr::FIGHTER, fighter))
		//mngr->addComponent<Follow>(e, mngr->getComponent<Transform>(mngr->setHandler(ecs::hdlr::FIGHTER, fighter)));

		// _currNumOfAsteroids++;
	}
}

void AsteroidsUtils::remove_all_asteroids()
{
	// grupo ASTEROIDS.
	const std::vector<ecs::Entity*>& asteroids = _mngr->getEntities(ecs::grp::ASTEROIDS);
	size_t n = asteroids.size();
	for (int i = 0; i < n; i++) {
		_mngr->setAlive(asteroids[i], false); // mata.
		_mngr->refresh(); // limpia el cadaver.
	}
}

void AsteroidsUtils::split_astroid(ecs::Entity* a)
{
	Generations* genComp = _mngr->getComponent<Generations>(a);
	int level = genComp->getGenerationLevel();

	// la desactiva.
	_mngr->setAlive(a, false); // mata.
	
	if (level - 1 > 0) {
		// genera asteroides mas pequenos.
		genComp->setGenerationLevel(level - 1);
		create_splitted_asteroids(&a);
	}

	_mngr->refresh(); // limpia el cadaver.
}
