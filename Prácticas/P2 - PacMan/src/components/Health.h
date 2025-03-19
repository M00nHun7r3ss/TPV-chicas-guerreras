#pragma once

#include "../ecs/Component.h"

class Texture;

class Health : public ecs::Component
{
public:

	Health();
	virtual ~Health();
	void render();
	void damage(int n);
	void heal();

	int getHealth() { return _currentHealth; }

private:
	int _currentHealth;
	int _maxHealth;
	Texture& _tex;
};