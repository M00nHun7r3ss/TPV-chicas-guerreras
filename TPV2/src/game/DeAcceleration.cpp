#include "DeAcceleration.h"

#include "../sdlutils/SDLUtils.h"
#include "Container.h"

DeAcceleration::DeAcceleration(): _lessFactor(0.995f) {
}

DeAcceleration::~DeAcceleration(){
}

void DeAcceleration::update(Container* o)
{
	Vector2D deceleration = o->getVel() * _lessFactor;
	o->setVel(deceleration);
}
