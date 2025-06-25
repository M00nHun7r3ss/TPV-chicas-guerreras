#pragma once

#include "../ecs/Component.h"
#include "../game/Game.h"
#include "../sdlutils/SDLUtils.h"

class RandomNumberGenerator;

struct ClonableGhostComponent : public ecs::Component
{
	ClonableGhostComponent(float n, float m) :
		_N(n), _M(m) {
	}

	virtual ~ClonableGhostComponent() {}

	void init();

	float _N; // veces que se puede clonar (cantidad de fantasmas que clona)
	float _M; // tiempo entre clones

	void releaseN() { _N--; }

	void setM(float m) { _M = m; }

	unsigned int _lastGhostCloned; // para el tiempo de cada clon.

};

