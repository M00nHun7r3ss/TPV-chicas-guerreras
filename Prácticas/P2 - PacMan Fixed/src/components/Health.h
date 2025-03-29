#pragma once

#include "../ecs/Component.h"

class Texture;

struct Health : public ecs::Component
{
	Health() : _tex() {}
	Health(Texture* tex) : _tex(tex) {}
	virtual ~Health() {}

	/*void damage(int n);
	void heal();

	int getHealth() { return _currentHealth; }*/

	int const MAX_HEALTH = 3;
	int _currentHealth;
	Texture* _tex;
};

