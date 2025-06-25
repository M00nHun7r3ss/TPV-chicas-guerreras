#pragma once

#include "../ecs/Component.h"
#include "../game/Game.h"
#include "../sdlutils/SDLUtils.h"

class RandomNumberGenerator;

struct ClonableGhostComponent : public ecs::Component
{
	ClonableGhostComponent(float n, float m) :
		_isClonable(false),
		_N(n), _M(m) {
	}

	virtual ~ClonableGhostComponent() {}

	void init();

	bool _isClonable; // define si es clonable o no 

	const float _N; // veces que se puede clonar (cantidad de fantasmas que clona)
	const float _M; // tiempo entre clones

	unsigned int _lastGhostCloned; // para el tiempo de cada clon.

};

