// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"
#include "../game/Game.h"
#include "../sdlutils/SDLUtils.h"

class RandomNumberGenerator;

class GhostSystem: public ecs::System {
public:

	GhostSystem();
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message &m) override;
private:
	void addGhosts(unsigned int n);
	void addClone(ecs::entity_t father);
	void deleteGhost(ecs::entity_t e);
	void removeAllGhosts();
	void generateGhostsByTime(bool immune);
	void moveGhosts();
	void manageClonableGhosts(ecs::entity_t ghost);
	void stopOnBorders(ecs::entity_t e);

	unsigned int _ghostLimit;
	unsigned int _currNumOfGhosts;
	unsigned int _lastGhostAdded;
	bool _canMove;
	bool _pmImmune;


	bool _ghostType; // F -> normal; T -> clonable (al crear el fantasma)

	RandomNumberGenerator& _rand;

};

