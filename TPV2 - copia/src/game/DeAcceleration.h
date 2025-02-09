#pragma once
#include "PhysicsComponent.h"

class DeAcceleration : public PhysicsComponent {
private:
	float _lessFactor;

public:
	DeAcceleration();
	virtual ~DeAcceleration();
	void update(Container* o) override;
};

