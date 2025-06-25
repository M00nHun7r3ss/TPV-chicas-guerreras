// This file is part of the course TPV2@UCM - Samir Genaim

#include "GhostSystem.h"

#include <algorithm>

#include "PacManSystem.h"
#include "ImmunitySystem.h"
#include "../components/ClonableGhostComponent.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

GhostSystem::GhostSystem()
	: _ghostLimit(10),
	_currNumOfGhosts(0),
	_lastGhostAdded(0),
	_canMove(false),
	_pmImmune(false),
	_rand(sdlutils().rand())
{
}

GhostSystem::~GhostSystem() {
}

void GhostSystem::initSystem() {
}

void GhostSystem::update() {

	//Comprobar que no este PM en estado inmune (si lo esta no aparecen nuevos)
	generateGhostsByTime(_pmImmune);

	// the Pacman's Immunity
	ImmunitySystem* pImmune = _mngr->getSystem<ImmunitySystem>();

	std::vector<ecs::entity_t> ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
	for (int i = 0; i < ghosts.size(); i++)
	{
		// --- IMAGE WITH FRAMES
		ImageWithFrames* iwf = _mngr->getComponent<ImageWithFrames>(ghosts[i]);
		if (pImmune->isImmune()) iwf->setColRow(iwf->getCol(), 6); // es azul
		else iwf->setColRow(iwf->getCol(), 4); // es rojo.

		// --- CLONABLE COMPONENT
		if (_mngr->hasComponent<ClonableGhostComponent>(ghosts[i]))
		{
			iwf->setColRow(iwf->getCol(), 7); // es morado
			manageClonableGhosts(ghosts[i]);
		}
		
	}
	//Movemos los fantasmas
	moveGhosts();
}

void GhostSystem::addGhosts(unsigned int n) {

	//Genera el numero pedido de fantasmas
	for (unsigned i = 0u; i < n; i++) {

		// add an entity to the manager
		ecs::entity_t e = _mngr->addEntity(ecs::grp::GHOSTS);

		// add a Transform component
		Transform* tr = _mngr->addComponent<Transform>(e);

		// clonable 10% prob
		int prob = _rand.nextInt(1, 2); // [1, 11).

		if (prob == 1) _ghostType = true; // clonable 
		else _ghostType = false; // no clonable.

		if (_ghostType)
		{
			//Anadimos el componente de fruta milagrosa con _N (_M vendra luego)
			float n = _rand.nextInt(1, 6); // [1, 6).
			_mngr->addComponent<ClonableGhostComponent>(e, n, 0); // inicialmente
		}

		int size = 30;

		int x, y;
		int velY; //Iniciamos la velocidad inicial como en la demo
		
		//Esquina por el que sale
			//0 - arriba/izqd, 1 - abajo/izqd, 2 - abajo/dcha, 3 - arriba/dcha
		int esquina = _rand.nextInt(0, 4); //Hasta max + 1, como el Rnd.Next de C#
		switch (esquina) //Esto es asi porque el origen del sprite es arriba izquierda 
		{
		case 0: //arriba/izqd
			x = 0;
			y = 0;
			velY = -1;
			break;
		case 1: //abajo/izqd,
			x = 0;
			y = sdlutils().height() - size;
			velY = 1;
			break;
		case 2: //abajo/dcha
			x = sdlutils().width() - size;
			y = sdlutils().height() - size;
			velY = 1;
			break;
		case 3: //arriba/dcha
			x = sdlutils().width() - size;
			y = 0;
			velY = -1;
			break;
		default:
			break;
		}

		//Inicializa transform
		tr->init(Vector2D(x, y), Vector2D(0, velY), size, size, 0.0f);

		// add an Image Component
		_mngr->addComponent<ImageWithFrames>(e, &sdlutils().images().at("sprites"), 0, 4, 8);
		
		_currNumOfGhosts++;
	}
}

void GhostSystem::addClone(ecs::entity_t father)
{
	// add an entity to the manager
	ecs::entity_t e = _mngr->addEntity(ecs::grp::GHOSTS);

	// add a Transform component
	Transform* tr = _mngr->addComponent<Transform>(e);

	int size = 30;

	Transform* f_tf = _mngr->getComponent<Transform>(father);

	//Inicializa transform
	tr->init(Vector2D(f_tf->_pos.getX(), f_tf->_pos.getY()), Vector2D(0, 0), size, size, 0.0f);

	// add an Image Component
	_mngr->addComponent<ImageWithFrames>(e, &sdlutils().images().at("sprites"), 0, 4, 8);

	_currNumOfGhosts++;
}

void GhostSystem::deleteGhost(ecs::entity_t e) {
	_mngr->setAlive(e, false);

	// play sound on channel 1 (if there is something playing there
	// it will be cancelled
	sdlutils().soundEffects().at("pacman_eat").play(0, 1);
}

void GhostSystem::removeAllGhosts()
{
	// grupo GHOSTS.
	const std::vector<ecs::entity_t>& ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
	size_t n = ghosts.size();
	for (int i = 0; i < n; i++) {
		deleteGhost(ghosts[i]);
	}
}

void GhostSystem::generateGhostsByTime(bool immune)
{
	//Si el pacman no es inmune, genera fantasmas
	if (!immune)
	{
		// Anade fantasma cada 5 segundos si hay menos de 10
		// Inicialmente empieza en 5 segundos.
		Uint32 _timeBetweenEachSpawn = 5000;

		VirtualTimer& vt = sdlutils().virtualTimer();

		if (vt.currRealTime() > _timeBetweenEachSpawn + _lastGhostAdded
			&& _currNumOfGhosts <= _ghostLimit) {
			addGhosts(1);

			_lastGhostAdded = vt.currRealTime();
		}
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
			if (_canMove){
				eTR->_vel = (pTR->_pos - eTR->_pos).normalize() * 0.9f;
			}

			// move the ghost
			eTR->_pos = eTR->_pos + eTR->_vel;
			//Para en los bordes y se da la vuelta
			stopOnBorders(e);
		}
	}
}

void GhostSystem::manageClonableGhosts(ecs::entity_t ghost)
{
	// lo sustrae.
	ClonableGhostComponent* cc = _mngr->getComponent<ClonableGhostComponent>(ghost);

	VirtualTimer& vt = sdlutils().virtualTimer();
	Uint32 _timeBetweenEachSpawn;

	cc->setM(_rand.nextInt(1000, 10001)); // [1000, 10001).
	_timeBetweenEachSpawn = cc->_M;


	if ((vt.currRealTime() > _timeBetweenEachSpawn + cc->_lastGhostCloned) // tiempo transcurriendo...
		&& cc->_N > 0) { // mientras N sea mayor que 0 sigue generando
		// pasado el tiempo:
		cc->_lastGhostCloned = vt.currRealTime();
		addClone(ghost); // crea un fantasma nacido de clonacion.
		cc->releaseN(); // reduce en 1 las clonaciones restantes
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

	//No reseteamos aqui el vt, porque lo hacemos en el pacman
	Message mes;

	switch (m.id)
	{
	case _m_ROUND_OVER:
		//Se quitan al salir de ronda. Al entrar se generan.
		removeAllGhosts();
		//Reseteamos el contador de tiempo
		_lastGhostAdded = 0;
		break;

	case _m_GAME_OVER:
		//Se quitan al salir de juego. Al entrar se generan.
		removeAllGhosts();
		//Reseteamos el contador de tiempo
		_lastGhostAdded = 0;
		break;


	case _m_IMMUNITY_START:

		// cuando hay inmunidad no se generan fantasmas.
		_pmImmune = true;
		break;

	case _m_PACMAN_GHOST_COLLISION:
		if (_mngr->getSystem<ImmunitySystem>()->isImmune())
		{
			deleteGhost(m.pacman_ghost_collision_data.g);
		}
		else
		{
			Game::State s;
			//Si no tienes vidas
			if (_mngr->getSystem<PacManSystem>()->getPacmanHealth() == 0)
			{
				// envia mensaje de fin de partida y cambia estado.
				mes.id = _m_GAME_OVER;
				s = Game::GAMEOVER;
			}
			//Si te quedan vidas, reinicias la ronda
			else
			{
				//Quita una vida
				_mngr->getSystem<PacManSystem>()->setPacmanDamage(1);
				// envia mensaje de fin de ronda y cambia estado.
				mes.id = _m_ROUND_OVER;
				s = Game::NEWROUND;
			}
			Game::Instance()->getManager()->send(mes);
			Game::Instance()->setState(s);
		}
		break;

	case _m_IMMUNITY_END: // no esta en inmunidad, no es que haya acabado en si.

		// cuando no hay inmunidad se generan fantasmas.
		_pmImmune = false;
		break;

	default:
		break;
	}


}