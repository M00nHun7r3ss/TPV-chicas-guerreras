// This file is part of the course TPV2@UCM - Samir Genaim

#include "GhostSystem.h"

#include <algorithm>
#include "../components/Image.h"
#include "../components/Points.h"
#include "../components/StarMotion.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrlSystem.h"

GhostSystem::GhostSystem() :
		_ghostLimit(30), _currNumOfGhost(0) {
}

GhostSystem::~GhostSystem() {
}

void GhostSystem::initSystem() {
}

void GhostSystem::update() {

	auto currTime = sdlutils().currRealTime();
	auto stars = _mngr->getEntities(ecs::grp::STARS);
	auto n = stars.size();

	for (auto i = 0u; i < n; i++) {
		auto tr = _mngr->getComponent<Transform>(stars[i]);
		auto starmotion = _mngr->getComponent<StarMotion>(stars[i]);

		if (starmotion->shouldUpdate(currTime)) {

			// rotate it
			tr->_rot += starmotion->_rot;

			// resize it
			tr->_width *= 0.95f;
			tr->_height *= 0.95f;

			// check if it should die
			if (tr->_width < starmotion->_sizeLimit
					|| tr->_height < starmotion->_sizeLimit) {
				_mngr->setAlive(stars[i], false);
				_currNumOfGhost--;
			}
		}
	}
}

void GhostSystem::addGhost(unsigned int n) {

	// Always use the random number generator provided by SDLUtils
	//
	RandomNumberGenerator& rand = sdlutils().rand();

	//unsigned limit = std::min( //
	//		static_cast<unsigned int>(n), 
	//		_ghostLimit - _currNumOfGhost);

	for (auto i = 0u; i < _ghostLimit; i++) {

		// add an entity to the manager
		ecs::entity_t e = _mngr->addEntity(ecs::grp::GHOSTS);

		// add a Transform component
		Transform* tr = _mngr->addComponent<Transform>(e);

		// --- POS ALEATORIA ---
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
		//
		_mngr->addComponent<Image>(e, &sdlutils().images().at("star"));

		//// add a StarMotion component to resize/rotate the star
		////
		//auto motion = _mngr->addComponent<StarMotion>(e);

		//motion->_rot = rand.nextInt(5, 10);
		//motion->_sizeLimit = rand.nextInt(2, 10);
		//motion->_updateFreq = rand.nextInt(20, 100);

		auto pts = _mngr->addComponent<Points>(e);
		pts->_points = rand.nextInt(1, 5);

		_currNumOfGhost++;
	}



	/*
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
	 */
}

void GhostSystem::onGhostEaten(ecs::entity_t e) {
	_mngr->setAlive(e, false);
	_currNumOfGhost--;

	// play sound on channel 1 (if there is something playing there
	// it will be cancelled
	sdlutils().soundEffects().at("pacman_eat").play(0, 1);
}

void GhostSystem::recieve(const Message &m) {
	switch (m.id) {
	case _m_GHOST_EATEN:
		onGhostEaten(m.ghost_eaten_data.e);
		break;
	case _m_CREATE_GHOST:
		addGhost(m.create_ghost_data.n);
		break;
	default:
		break;
	}
}
