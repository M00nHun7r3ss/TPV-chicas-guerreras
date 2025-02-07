#pragma once
#include "PhysicsComponent.h"

class DeAcceleration : public PhysicsComponent {
private:
	float _lessFactor = 0.995f;

public:
	DeAcceleration();
	virtual ~DeAcceleration();
	void update(Container* o) override;
};

