#include "ShieldSystem.h"

#include "../ecs/Manager.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"

ShieldSystem::ShieldSystem()
	: _isShieldOn(false),
	_lastShieldStarted(0),
	_N(), _M(), _X(30.0f), _T() {
}

ShieldSystem::~ShieldSystem() {
}

void ShieldSystem::initSystem() {
}

void ShieldSystem::update()
{
	VirtualTimer& vt = sdlutils().virtualTimer();
	Message mes;

	// si esta en escudo...
	//if (_isShieldOn)
	//{
	//	_T = 5000; // 5S

	//	//Pasado ese tiempo
	//	if (vt.currRealTime() > _T + _lastShieldStarted) {
	//		_isShieldOn = false; // pasados los 5s apaga el escudo
	//	}
	//}

	moveShield();
}

void ShieldSystem::recieve(const Message& m)
{
	// en caso de que la entidad fruta sea milagrosa.
	//ecs::entity_t e = m.pacman_food_collision_data.f;
	switch (m.id) {
	case _m_IMMUNITY_START:
		endShield();
		break;
	case _m_ROUND_OVER:
		endShield();
		_N = 0;
		break;
	case _m_ROUND_START:
		createShield();
		break;
	default:
		break;
	}
}

void ShieldSystem::createShield()
{
	//tamano
	int size = 30;

	for (unsigned i = 0u; i < SHIELD_STARS; i++) {

		// add an entity to the manager
		ecs::entity_t e = _mngr->addEntity(ecs::grp::SHIELDS);

		// add a Transform component
		Transform* tr = _mngr->addComponent<Transform>(e);

		_isShieldOn = true;

		// inicialmente cereza.
		_mngr->addComponent<Image>(e, &sdlutils().images().at("star"));

		tr->init(Vector2D(-5, -5), Vector2D(), size, size, 0.0f); // al principio fuera de pantalla (invisibles)
	}
}

void ShieldSystem::endShield()
{
	_isShieldOn = false;
	_N = 0;
}

void ShieldSystem::moveShield()
{
	// obtenemos datos
	std::vector<ecs::entity_t> stars = _mngr->getEntities(ecs::grp::SHIELDS); // estrellas
	ecs::entity_t pm = _mngr->getHandler(ecs::hdlr::PACMAN); // pacman
	Transform* pTR = _mngr->getComponent<Transform>(pm); // pacmans transform

	
	for (int i = 0; i < stars.size(); i++)
	{
		// + pTR->_width/5 es para ajustarlo al centro
		float x = pTR->_pos.getX() + pTR->_width/5;
		float y = pTR->_pos.getY() + pTR->_height/5;
		Transform* s_tf = _mngr->getComponent<Transform>(stars[i]);
		switch (i)
		{
		case 0: // primera p+(X,0)
			x += _X;
			break;
		case 1: // segunda p-(X,0)
			x -= _X;
			break;
		case 2: // tercera p+(0,X)
			y += _X;
			break;
		default: // cuarta p-(0,X)
			y -= _X;
			break;
		}

		s_tf->_pos.set(x, y);
	}

}
