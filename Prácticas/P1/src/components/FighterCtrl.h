#pragma once
#include "../ecs/Component.h"

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
	//void createStart();
	Transform* _tr;
};

