#pragma once

#include "AsteroidsFacade.h"

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
	inline int getAsteroidNumber() { return _n; }
private:
	Vector2D _centroVent;
	ecs::Manager* _mngr;
	int _n; // nº de asteroides.

	void create_splitted_asteroids(ecs::entity_t* a); // no hay n porque siempre se crean 2. "a" es el asteroide del que salen al romperse.
};

