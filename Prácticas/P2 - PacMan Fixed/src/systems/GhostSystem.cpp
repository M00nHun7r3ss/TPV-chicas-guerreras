// This file is part of the course TPV2@UCM - Samir Genaim

#include "GhostSystem.h"

#include <algorithm>
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

GhostSystem::GhostSystem() 
	: _ghostLimit(10), 
	  _currNumOfGhosts(0), 
	  _lastGhostAdded(0) {
}

GhostSystem::~GhostSystem() {
}

void GhostSystem::initSystem() {
}

void GhostSystem::update() {

	uint32_t currTime = sdlutils().currRealTime();
	std::vector<ecs::entity_t> ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
	size_t n = ghosts.size();

	// Anade fantasma cada 5 segundos si hay menos de 10
	// Inicialmente empieza en 5 segundos.
	Uint32 _timeBetweenEachSpawn = 5000;

	VirtualTimer& vt = sdlutils().virtualTimer();


	bool timer = vt.currTime() > _timeBetweenEachSpawn + _lastGhostAdded;
	bool nGhosts = _currNumOfGhosts <= _ghostLimit;
													   
	if (timer && nGhosts){
		addGhost(1);
		_lastGhostAdded = vt.currTime();
	}
}

void GhostSystem::addGhost(unsigned int n) {

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

void GhostSystem::onGhostEaten(ecs::entity_t e) {
	_mngr->setAlive(e, false);
	_currNumOfGhosts--;

	// play sound on channel 1 (if there is something playing there
	// it will be cancelled
	sdlutils().soundEffects().at("pacman_eat").play(0, 1);
}

void GhostSystem::removeAllGhosts()
{
	// Cuando acaba una ronda quita todos los fantasmas actuales.
	_currNumOfGhosts = 0;

	// grupo GHOSTS.
	const std::vector<ecs::entity_t>& ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
	size_t n = ghosts.size();
	for (int i = 0; i < n; i++) {
		_mngr->setAlive(ghosts[i], false); // mata.
	}
}

void GhostSystem::recieve(const Message &m) {
	switch (m.id) {
	case _m_GHOST_EATEN:
		onGhostEaten(m.ghost_eaten_data.e);
		break;

	case _m_CREATE_GHOSTS:
		addGhost(m.create_ghost_data.n);
		break;

	case _m_ROUND_OVER:
		removeAllGhosts(); //Se quitan al salir de ronda. Al entrar se generan.
		break;
	default:
		break;
	}
}
