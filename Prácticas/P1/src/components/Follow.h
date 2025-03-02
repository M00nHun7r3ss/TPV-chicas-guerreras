#pragma once
#include <SDL_stdinc.h>

#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform;
class Follow : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::FOLLOW)

	Follow();
	Follow(Vector2D playerPos);
	virtual ~Follow();
	void initComponent() override;
	void update() override;

private:

	// --- asteroide.
	Transform* _tr; // transform asteroide.
	Vector2D _vel; // velocidad asteroide.
	Vector2D _pos; // posicion asteroide.

	Vector2D _playerPos; // posicion fighter.
};

