#pragma once

#include "AsteroidsFacade.h"

class Transform;
class AsteroidsUtils : public AsteroidsFacade
{
	__CMPID_DECL__(ecs::cmp::ASTEROIDFACADE)

	AsteroidsUtils() {
	}
	virtual ~AsteroidsUtils() {
	}
	void create_asteroids(int n) override;
	void remove_all_asteroids() override;
	void split_astroid(ecs::Entity* a) override;
};

