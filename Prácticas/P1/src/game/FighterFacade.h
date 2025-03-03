#pragma once

#include "../ecs/ecs.h"
#include "../game/Game.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class FighterFacade {
public:
	FighterFacade() {}
	virtual ~FighterFacade() {}
	void virtual create_fighter() = 0;
	void virtual reset_fighter() = 0;
	void virtual reset_lives() = 0;
	int virtual update_lives(int n) = 0;
};

