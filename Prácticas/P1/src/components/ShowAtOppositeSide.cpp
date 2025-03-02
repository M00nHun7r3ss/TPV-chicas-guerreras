#include "ShowAtOppositeSide.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

ShowAtOppositeSide::ShowAtOppositeSide() : _tr() {
}

ShowAtOppositeSide::~ShowAtOppositeSide(){
}

void ShowAtOppositeSide::initComponent() {
	auto* mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void ShowAtOppositeSide::update()
{
	// posicion.
	float posX = _tr->getPos().getX();
	float posY = _tr->getPos().getY();

	// limites.
	auto width = sdlutils().width();
	auto height = sdlutils().height();

	// las X.
	if (posX < 0) _tr->getPos().setX(width);
	else if (posX > width) _tr->getPos().setX(0);

	// las Y.
	if (posY < 0) _tr->getPos().setY(height);
	else if (posY > height) _tr->getPos().setY(0);

}
