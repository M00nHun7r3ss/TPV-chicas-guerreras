// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"

#include <vector>

#include "ImmunitySystem.h"

CollisionsSystem::CollisionsSystem() {
}

CollisionsSystem::~CollisionsSystem() {
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {

	// the Pacman's Transform
	ecs::entity_t pm = _mngr->getHandler(ecs::hdlr::PACMAN);
	Transform* pTR = _mngr->getComponent<Transform>(pm);

	// Collisions P-G
	collisionPacmanGhosts(pTR);
	// Collisions P-F
	collisionPacmanFruits(pTR);
	// Collisions Shield
	collisionWithShield();
}

void CollisionsSystem::collisionPacmanGhosts(Transform* ptf)
{
	std::vector<ecs::entity_t> ghost = _mngr->getEntities(ecs::grp::GHOSTS);
	size_t n = ghost.size();
	for (unsigned i = 0u; i < n; i++) {
		ecs::entity_t e = ghost[i];
		if (_mngr->isAlive(e)) { // if the ghost is active (it might have died in this frame)

			// the ghost's Transform
			auto eTR = _mngr->getComponent<Transform>(e);
			Message m;
			// check if PacMan collides with the ghost (i.e., eat it)
			if (Collisions::collides(			//
				ptf->_pos, ptf->_width, ptf->_height, //
				eTR->_pos, eTR->_width, eTR->_height)) {

				// pasamos el fantasma concreto.
				m.id = _m_PACMAN_GHOST_COLLISION;
				m.pacman_ghost_collision_data.g = e;
				_mngr->send(m);
			}

		}
	}
}

void CollisionsSystem::collisionPacmanFruits(Transform* ptf)
{
	std::vector<ecs::entity_t> fruit = _mngr->getEntities(ecs::grp::FRUITS);
	size_t k = fruit.size();
	for (unsigned i = 0u; i < k; i++) {
		ecs::entity_t e = fruit[i];
		if (_mngr->isAlive(e)) { // if the fruit is active (it might have died in this frame)

			// the fruit's Transform
			//
			auto eTR = _mngr->getComponent<Transform>(e);

			Message z;
			// check if PacMan collides with the fruit (i.e., eat it)
			if (Collisions::collides(			//
				ptf->_pos, ptf->_width, ptf->_height, //
				eTR->_pos, eTR->_width, eTR->_height)) {

				z.id = _m_PACMAN_FOOD_COLLISION;
				//Le pasamos la fruta concreta
				z.pacman_food_collision_data.f = e;
				_mngr->send(z);
			}
		}
	}
}

void CollisionsSystem::collisionWithShield()
{
}

