#pragma once
#include "../ecs/Component.h"

class Transform;

class Health : public ecs::Component
{
public:

	__CMPID_DECL__(ecs::cmp::HEALTH)

	Health();
	virtual ~Health();
	void render() override;
	void update();
	void damage();
	void heal();
	int getHealth() { return _currentHealth; }

private:
	int _currentHealth;
	int _maxHealth;
	Transform* _tr;
};

