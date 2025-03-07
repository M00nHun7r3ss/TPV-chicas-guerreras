#pragma once
#include "../ecs/ecs.h"
#include "../game/Game.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

using ecs::entity_t;

class AsteroidsFacade {
protected:
	AsteroidsFacade() {
	}
	virtual ~AsteroidsFacade() {
	}
	virtual void create_asteroids(int n) = 0;
	virtual void remove_all_asteroids() = 0;
	virtual void split_asteroid(ecs::Entity* a) = 0;
};