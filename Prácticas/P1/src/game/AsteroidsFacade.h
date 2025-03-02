#pragma once
#include "../ecs/ecs.h"
#include "../game/Game.h"

using ecs::entity_t;

class AsteroidsFacade {
protected:
	AsteroidsFacade() {
	}
	virtual ~AsteroidsFacade() {
	}
	virtual void create_asteroids(int n) = 0;
	virtual void remove_all_asteroids() = 0;
	virtual void split_astroid(ecs::Entity* a) = 0;
};