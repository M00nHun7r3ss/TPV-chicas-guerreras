#pragma once
#include <SDL_stdinc.h>

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../game/Game.h"

class Transform;
class Follow : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::FOLLOW)

	Follow();
	Follow(ecs::entity_t fighter);
	virtual ~Follow();
	void initComponent() override;
	void update() override;

private:

	// --- asteroide.
	Transform* _tr; // transform asteroide.
	Vector2D _vel; // velocidad asteroide.
	Vector2D _pos; // posicion asteroide.

	// --- caza.
	ecs::entity_t _fighter; // fighter
	Transform* _tFighter; // transform caza.

};

