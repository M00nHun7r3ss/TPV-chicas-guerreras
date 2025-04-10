// This file is part of the course TPV2@UCM - Samir Genaim

#include "GhostSystem.h"

#include <algorithm>

#include "PacManSystem.h"
#include "../components/Health.h"
#include "../components/ImageWithFrames.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

GhostSystem::GhostSystem()
	: _ghostLimit(10),
	_currNumOfGhosts(0),
	_lastGhostAdded(0),
	_canMove(false) {
}

GhostSystem::~GhostSystem() {
}

void GhostSystem::initSystem() {
}

void GhostSystem::update() {

	//Comprobar que no este PM en estado inmune (si lo esta no aparecen nuevos)
	generateGhostsByTime();

	//Movemos los fantasmas
	moveGhosts();
}

void GhostSystem::addGhost(unsigned int n) {

	// Always use the random number generator provided by SDLUtils
	RandomNumberGenerator& rand = sdlutils().rand();

	//Genera el numero pedido de fantasmas
	for (unsigned i = 0u; i < n; i++) {

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
		_mngr->addComponent<Image>(e, &sdlutils().images().at("sprites"));
		//_mngr->addComponent<ImageWithFrames>(e, &sdlutils().images().at("sprites"), 8, 8);
		
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

void GhostSystem::generateGhostsByTime()
{
	// Anade fantasma cada 5 segundos si hay menos de 10
	// Inicialmente empieza en 5 segundos.
	Uint32 _timeBetweenEachSpawn = 5000;

	VirtualTimer& vt = sdlutils().virtualTimer();

	if (vt.currRealTime() > _timeBetweenEachSpawn + _lastGhostAdded
		&& _currNumOfGhosts <= _ghostLimit) {
		addGhost(1);
		
		_lastGhostAdded = vt.currRealTime();
	}
}

void GhostSystem::moveGhosts()
{
	// the Pacman's Transform
	ecs::entity_t pm = _mngr->getHandler(ecs::hdlr::PACMAN);
	Transform* pTR = _mngr->getComponent<Transform>(pm);

	// Movemos los fantasmas
	std::vector<ecs::entity_t> ghost = _mngr->getEntities(ecs::grp::GHOSTS);
	size_t n = ghost.size();
	for (unsigned i = 0u; i < n; i++) {
		ecs::entity_t e = ghost[i];
		if (_mngr->isAlive(e)) { // if the ghost is active (it might have died in this frame)

			// the ghost's Transform
			Transform* eTR = _mngr->getComponent<Transform>(e);

			RandomNumberGenerator& rand = sdlutils().rand();
			int prob = rand.nextInt(1, 501); // [1, 501).

			if (prob == 1) _canMove = true; // se movera.
			else _canMove = false; // no se movera.

			//Actualizamos su vector velocidad
			if (_canMove)
			{
				eTR->_vel = (pTR->_pos - eTR->_pos).normalize() * 0.9f;
			}

			// move the ghost
			eTR->_pos = eTR->_pos + eTR->_vel;
			//Para en los bordes y se da la vuelta
			stopOnBorders(e);
		}
	}
}

void GhostSystem::stopOnBorders(ecs::entity_t e)
{
	// the ghost's Transform
	Transform* eTR = _mngr->getComponent<Transform>(e);
	// check left/right borders
	if (eTR->_pos.getX() < 0) {
		eTR->_pos.setX(0.0f);
		//Change vel in x
		eTR->_vel.set(-eTR->_vel.getX(), eTR->_vel.getY());
	}
	else if (eTR->_pos.getX() + eTR->_width > sdlutils().width()) {
		eTR->_pos.setX(sdlutils().width() - eTR->_width);
		//Change vel in x
		eTR->_vel.set(-eTR->_vel.getX(), eTR->_vel.getY());
	}

	// check upper/lower borders
	if (eTR->_pos.getY() < 0) {
		eTR->_pos.setY(0.0f);
		//Change vel in y
		eTR->_vel.set(eTR->_vel.getX(), -eTR->_vel.getY());
	}
	else if (eTR->_pos.getY() + eTR->_height > sdlutils().height()) {
		eTR->_pos.setY(sdlutils().height() - eTR->_height);
		//Change vel in y
		eTR->_vel.set(eTR->_vel.getX(), -eTR->_vel.getY());
	}
}

void GhostSystem::recieve(const Message& m) {

	Message mes;

	if (m.id == _m_ROUND_OVER)
	{
		//Se quitan al salir de ronda. Al entrar se generan.
		removeAllGhosts();
	}
	else if (m.id == _m_IMMUNITY_START)
	{
		// TODO: cambia el sprite fantasma.

		if (m.id == _m_PACMAN_GHOST_COLLISION)
		{
			// TODO: desaparece el fantasma.
		}
	}
	else if (m.id == _m_IMMUNITY_END)
	{
		// cuando no hay inmunidad se generan fantasmas.
		generateGhostsByTime();

		if (m.id == _m_PACMAN_GHOST_COLLISION)
		{
			// TODO: muere el pacman.

			Game::State s;
			if (_mngr->getSystem<PacManSystem>()->getPacmanHealth() <= 0)
			{
				// envia mensaje de fin de partida y cambia estado.
				mes.id = _m_GAME_OVER;
				s = Game::NEWROUND;
			}
			else
			{
				// envia mensaje de fin de ronda y cambia estado.
				mes.id = _m_ROUND_OVER;
				s = Game::GAMEOVER;
			}
			Game::Instance()->getManager()->send(mes);
			Game::Instance()->setState(s);
		}
	}

}