#include "ShowAtOppositeSide.h"

#include "Transform.h"

#include <cassert>

#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"

ShowAtOppositeSide::ShowAtOppositeSide() : _tr() {
}

ShowAtOppositeSide::~ShowAtOppositeSide(){
}

void ShowAtOppositeSide::initComponent() {
	ecs::Manager* mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void ShowAtOppositeSide::update()
{
	// posicion.
	float posX = _tr->getPos().getX();
	float posY = _tr->getPos().getY();

	// limites.
	int width = sdlutils().width();
	int height = sdlutils().height();

	// las X.
	if (posX + _tr->getWidth() < 0) _tr->getPos().setX(width); // para que se haga bien con el tamano nave
	else if (posX > width) _tr->getPos().setX(- _tr->getWidth()); // para que al salir salga con su tamano

	// las Y.
	if (posY + _tr->getHeight() < 0) _tr->getPos().setY(height); // para que se haga bien con el tamano nave
	else if (posY > height) _tr->getPos().setY(- _tr->getHeight()); // para que al salir salga con su tamano
}
