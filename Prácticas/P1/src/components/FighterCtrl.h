#pragma once

#include "../ecs/Component.h"

#include "../game/Game.h"

class Transform;

class FighterCtrl : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::FIGHTERCTRL)

	FighterCtrl();
	virtual ~FighterCtrl();
	void initComponent() override;
	void update() override;
	
private:
	Transform* _tr;
};

