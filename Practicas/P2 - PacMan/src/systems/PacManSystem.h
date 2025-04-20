// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../components/Health.h"
#include "../ecs/System.h"

struct Transform;

class PacManSystem: public ecs::System {
public:

	PacManSystem();
	virtual ~PacManSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& m) override;

	inline int getPacmanHealth() { return _pmHealth->getHealth(); }
	inline void setPacmanDamage(int i) { _pmHealth->damage(i); }
	
private:
	void resetPacman();
	void stopOnBorders();
	void pacmanInput();
	void maxHealth();

	Transform *_pmTR;
	Health* _pmHealth;
};

