#pragma once

#include "../ecs/Component.h"
#include "../game/Game.h"
#include "../sdlutils/SDLUtils.h"

class RandomNumberGenerator;

struct MiraculousComponent : public ecs::Component
{
	MiraculousComponent(float n, float m) : 
		_isMiraculous(false),
		_N(n), _M(m) {}

	virtual ~MiraculousComponent() {}

	void init();

	bool _isMiraculous; // define si es milagrosa o no en este momento

	float _N; // tiempo en normal.
	float _M; // tiempo en milagroso.

};

