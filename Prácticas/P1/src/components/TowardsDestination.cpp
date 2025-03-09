#include "TowardsDestination.h"

#include "Transform.h"

#include <cassert>

#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"

TowardsDestination::TowardsDestination()
	:_tr() {
}

TowardsDestination::~TowardsDestination() {
}

void TowardsDestination::initComponent() {
	ecs::Manager* mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void TowardsDestination::update() {

	_pos = _tr->getPos();
	_vel = _tr->getVel();

	Vector2D newPos = randomPos();

	//Si ha llegado al destino
	if (_pos.getX() == newPos.getX() && _pos.getY() == newPos.getY())
	{
		//Cambia la posicion destino
		newPos = randomPos();
	}

	//Se mueve
	_tr->getVel().set(_vel.rotate(_vel.angle(newPos - _pos)));

}

Vector2D TowardsDestination::randomPos()
{
	// Always use the random number generator provided by SDLUtils
	RandomNumberGenerator& rand = sdlutils().rand();

	int x = rand.nextInt(-10, 11);
	int y = rand.nextInt(-10, 11);

	_destPos.setX(_destPos.getX() + x);
	_destPos.setY(_destPos.getY() + y);

	return _destPos;
}

