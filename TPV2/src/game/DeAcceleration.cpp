#include "DeAcceleration.h"

#include "../sdlutils/SDLUtils.h"
#include "Container.h"

DeAcceleration::DeAcceleration(){
}

DeAcceleration::~DeAcceleration(){
}

void DeAcceleration::update(Container* o)
{
	Vector2D deceleration = o->getVel() * _lessFactor;
	o->setVel(deceleration);
}
