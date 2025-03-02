#pragma once

#include "AsteroidsFacade.h"
#include "../utils/Vector2D.h"


class Transform;
class AsteroidsUtils : public AsteroidsFacade
{
public:
	__CMPID_DECL__(ecs::cmp::ASTEROIDFACADE)

	AsteroidsUtils();
	virtual ~AsteroidsUtils(){}

	void create_asteroids(int n) override;
	void remove_all_asteroids() override;
	void split_astroid(ecs::Entity* a) override;

private:
	Vector2D _centroVent;
	ecs::Manager* _mngr;
};

