// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class GhostSystem: public ecs::System {
public:

	GhostSystem();
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
	void addGhost(unsigned int n);
	void onGhostEaten(ecs::entity_t e);
	void removeAllGhosts();
	void recieve(const Message &m) override;
private:
	unsigned int _ghostLimit;
	unsigned int _currNumOfGhost;
};

