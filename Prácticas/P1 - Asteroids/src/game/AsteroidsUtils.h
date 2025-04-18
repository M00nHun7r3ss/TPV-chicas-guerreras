#pragma once

#include "AsteroidsFacade.h"

#include "../sdlutils/SDLUtils.h"

class Transform;

class AsteroidsUtils : public AsteroidsFacade
{
public:
	__CMPID_DECL__(ecs::cmp::ASTEROIDFACADE)

	AsteroidsUtils();
	virtual ~AsteroidsUtils(){}

	void create_asteroids(int n) override;
	void remove_all_asteroids() override;
	void split_asteroid(ecs::Entity* a) override;

	// getter n asteroids.
	inline int getAsteroidNumber() override { return _n; }
private:
	Vector2D _centroVent;
	ecs::Manager* _mngr;
	int _n; // n� de asteroides.
	RandomNumberGenerator& _rand;

	void create_splitted_asteroids(ecs::entity_t* a, int lvl); // no hay n porque siempre se crean 2. "a" es el asteroide del que salen al romperse.
};

