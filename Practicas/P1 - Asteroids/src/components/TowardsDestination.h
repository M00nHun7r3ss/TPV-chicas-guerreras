#pragma once
#include <SDL_stdinc.h>

#include "../ecs/Component.h"

#include "../utils/Vector2D.h"

#include "../game/Game.h"

class Transform;
class TowardsDestination : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::TOWARDDESTINATION)

	TowardsDestination();
	TowardsDestination(ecs::entity_t fighter);
	virtual ~TowardsDestination();
	void initComponent() override;
	void update() override;

private:

	// --- asteroide.
	Transform* _tr; // transform asteroide.
	Vector2D _vel; // velocidad asteroide.
	Vector2D _pos; // posicion asteroide.

	// --- target
	Vector2D _destPos; // posicion destino

	Vector2D randomPos();
};

