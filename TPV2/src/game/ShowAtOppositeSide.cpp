#include "ShowAtOppositeSide.h"

#include "../sdlutils/SDLUtils.h"
#include "Container.h"

ShowAtOppositeSide::ShowAtOppositeSide(){
}

ShowAtOppositeSide::~ShowAtOppositeSide(){
}

void ShowAtOppositeSide::update(Container* o)
{
	// posicion.
	float posX = o->getPos().getX();
	float posY = o->getPos().getY();

	// limites.
	auto width = sdlutils().width();
	auto height = sdlutils().height();

	// las X.
	if (posX < 0) o->getPos().setX(width);
	else if (posX > width) o->getPos().setX(0);

	// las Y.
	if (posY < 0) o->getPos().setY(height);
	else if (posY > height) o->getPos().setY(0);

}
