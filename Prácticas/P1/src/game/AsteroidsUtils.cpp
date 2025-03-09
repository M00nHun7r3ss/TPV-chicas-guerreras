#include "AsteroidsUtils.h"

#include <algorithm>
#include <vector>

#include "../ecs/Manager.h"
#include "../ecs/Entity.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/Texture.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "../components/TowardsDestination.h"
#include "../components/ImageWithFrames.h"

AsteroidsUtils::AsteroidsUtils()
	: _centroVent((float)(sdlutils().width() / 2), (float)(sdlutils().height() / 2)),
	  _mngr(Game::Instance()->getManager()),
	  _n(0), // inicialmente 0.
      _rand(sdlutils().rand())
{
}

void AsteroidsUtils::create_asteroids(int n)
{
	_n += n;

	for (int i = 0; i < n; i++){
		// add and entity to the manager
		ecs::entity_t e = _mngr->addEntity(ecs::grp::ASTEROIDS);

		// add a Transform component, and initialise it with random size and position
		Transform* tr = _mngr->addComponent < Transform >(e);
		Generations* gen = _mngr->addComponent<Generations>(e); // add Generations Component
		gen->generate(); // and makes the generation.

		// --- POS ALEATORIA ---
		int size = gen->getGenerationSize();

		//Lado por el que sale
		//0 - arriba, 1 - abajo, 2 - izqd, 3 - dcha
		int lado = _rand.nextInt(0, 4); //Hasta max + 1, como el Rnd.Next de C#
		int x, y;
		switch (lado) //Esto es asi porque el origen del sprite es arriba izquierda 
		{
		case 0: //Arriba
			x = _rand.nextInt(0, sdlutils().width() - size);
			y = _rand.nextInt(0, size);
			break;
		case 1: //Abajo
			x = _rand.nextInt(0, sdlutils().width() - size);
			y = _rand.nextInt(sdlutils().height() - 2 * size, sdlutils().height() - size);
			break;
		case 2: //Izquierda
			x = _rand.nextInt(0, size);
			y = _rand.nextInt(0, sdlutils().height() - size);
			break;
		case 3: //Derecha
			x = _rand.nextInt(sdlutils().width() - 2 * size, sdlutils().width() - size);
			y = _rand.nextInt(0, sdlutils().height() - size);
			break;
		default:
			break;
		}

		// --- VELOCIDAD ALEATORIA --- (case 2)
		//Centro ventana para que los asteroides vayan hacia el centro
		int rx = _rand.nextInt(-100, 101);
		int ry = _rand.nextInt(-100, 101);
		Vector2D centro = { _centroVent.getX() + rx, _centroVent.getY() + ry };

		float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
		Vector2D v = (centro - Vector2D(x, y)).normalize() * speed;

		// inicializa el asteroide en ese transform
		tr->init(Vector2D(x, y), v, size, size, 0.0f);

		// Los demas componentes
		_mngr->addComponent<ShowAtOppositeSide>(e); // add ShowAtOppositeSide Component.

		std::string text;

		int comp = _rand.nextInt(0, 3); // para que salga 0 -> follow; 1-> towardsdestination, 2 -> va al centro
		if (comp == 0) // FOLLOW (case 0)
		{
			entity_t fighter = _mngr->getHandler(ecs::hdlr::FIGHTER);
			_mngr->addComponent<Follow>(e, fighter);

			text = "asteroid_gold"; // add an Image With Frames Component Dorado
		}
		else if (comp == 1) // TOWARDSDESTINATION (case 1)
		{
			_mngr->addComponent<TowardsDestination>(e);

			text = "asteroid"; // add an Image With Frames Component Plateado
		}
		else // para el --- Velocidad aleatoria (case 2)
		{
			text = "asteroid"; // add an Image With Frames Component Plateado
		}

		_mngr->addComponent<ImageWithFrames>(e, &sdlutils().images().at(text), 6, 5); 

	}
}

void AsteroidsUtils::create_splitted_asteroids(entity_t* a, int lvl)
{
	// se crea asteroide.
	_n++;

	// add and entity to the manager
	ecs::entity_t e = _mngr->addEntity(ecs::grp::ASTEROIDS);

	// add a Transform component, and initialise it with random size and position
	Transform* tr = _mngr->addComponent < Transform >(e);

	// --- VELOCIDAD Y POSICION---
	Transform* aTf = _mngr->getComponent<Transform>(*a);

	float size = 10.0f + 5.0f * (lvl + 1); // (lvl + 1) pa q no haga 0* algo

	int r = _rand.nextInt(0, 360);
	Vector2D pos = aTf->getPos() + aTf->getVel().rotate(r) * 2 * std::max(size, size);
	Vector2D vel = aTf->getVel().rotate(r) * 1.1f;

	// inicializa el asteroide en ese transform
	tr->init(pos, vel, size, size, r);

	// --- generations del e (splitted).
	_mngr->addComponent<Generations>(e);
	Generations* gen = _mngr->getComponent<Generations>(e);

	// Queremos que el hijo tenga 1 menos que el padre.
	gen->setGenerationLevel(lvl - 1);

	// Los demas componentes
	_mngr->addComponent<ShowAtOppositeSide>(e); // add ShowAtOppositeSide Component.

	std::string text;
	int comp = _rand.nextInt(0, 2); // para que salga 0 -> follow; 1-> towardsdestination
	if (comp == 0) // FOLLOW (case 0)
	{
		entity_t fighter = _mngr->getHandler(ecs::hdlr::FIGHTER);
		_mngr->addComponent<Follow>(e, fighter);

		text = "asteroid_gold"; // add an Image With Frames Component Dorado
	}
	else if (comp == 1) // TOWARDSDESTINATION (case 1)
	{
		_mngr->addComponent<TowardsDestination>(e);

		text = "asteroid"; // add an Image With Frames Component Plateado
	}

	_mngr->addComponent<ImageWithFrames>(e, &sdlutils().images().at(text), 6, 5);

}

void AsteroidsUtils::remove_all_asteroids()
{
	_n = 0; // se borran todos.

	// grupo ASTEROIDS.
	const std::vector<ecs::entity_t>& asteroids = _mngr->getEntities(ecs::grp::ASTEROIDS);
	size_t n = asteroids.size();
	for (int i = 0; i < n; i++) {
		_mngr->setAlive(asteroids[i], false); // mata.
	}

}

void AsteroidsUtils::split_asteroid(ecs::Entity* a)
{

	Generations* genComp = _mngr->getComponent<Generations>(a);
	int level = genComp->getGenerationLevel();

	// la desactiva.
	_mngr->setAlive(a, false); // mata.
	_n--; // se quita el asteroide splitteado.

	sdlutils().soundEffects().at("hit").play(0, 1); // destruye asteroide

	if (level > 0)
	{
		for (int i = 0; i < 2; i++)
		{
			create_splitted_asteroids(&a, level-1);
		}
	}

}
