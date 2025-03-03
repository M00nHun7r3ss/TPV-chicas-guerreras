#pragma once
#include "FighterFacade.h"



class Transform;
class FighterUtils : public FighterFacade {

public:

	__CMPID_DECL__(ecs::cmp::FIGHTERFACADE)

	FighterUtils();
	virtual ~FighterUtils() {}
	void create_fighter() override;
	void reset_fighter() override {}
	void reset_lives() override {}
	int update_lives(int n) override { return 1; }

private:
	ecs::Manager* _mngr;
};
