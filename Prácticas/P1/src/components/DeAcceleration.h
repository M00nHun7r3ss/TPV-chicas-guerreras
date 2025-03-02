#pragma once
#include "../ecs/Component.h"
#include "../game/Game.h"

class Vector2D;
class Transform;

class DeAcceleration : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::DEACCELERATION)

	DeAcceleration();
	virtual ~DeAcceleration();
	void initComponent() override;
	void update() override;
private:
	float _lessFactor; // para ir desacelerando.
	float _stopFactor; // para parar.
	Transform* _tr;
};

