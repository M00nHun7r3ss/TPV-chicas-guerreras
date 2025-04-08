#pragma once

#include "../ecs/Component.h"
#include "../game/Game.h"
#include "../sdlutils/SDLUtils.h"

class RandomNumberGenerator;

struct MiraculousComponent : public ecs::Component
{
	MiraculousComponent() : 
		_lastFruitChanged(0),
		_isMiraculous(false),
		_rand(sdlutils().rand()),
		_N(0), _M(0) {}

	virtual ~MiraculousComponent() {}

	void init();
	void update();

	unsigned int _lastFruitChanged;

	bool _isMiraculous; // define si es milagrosa o no en este momento

	// random sdlutils generator.
	RandomNumberGenerator& _rand;

	float _N; // tiempo en normal.
	float _M; // tiempo en milagroso.

};

