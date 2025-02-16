#pragma once
#include "../ecs/Component.h"

class Health : public ecs::Component
{
public:

	__CMPID_DECL__(ecs::cmp::HEALTH)

	Health();
	virtual ~Health();
	void initComponent() override;
	void render() override;
	void update();
	void damage();
	void heal();
	int getHealth() { return _currentHealth; }

private:
	int _currentHealth;
	int _maxHealth;
};

