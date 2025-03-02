// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "../ecs/Component.h"

class Transform;
class AsteroidMotion: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::STARMOTION)

	AsteroidMotion();
	virtual ~AsteroidMotion();
	void initComponent() override;
	void update() override;

private:
	Transform *_tr;
	Uint32 _lastUpdate;
};

