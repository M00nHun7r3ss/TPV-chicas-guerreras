// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

struct Transform;

class PacManSystem: public ecs::System {
public:

	PacManSystem();
	virtual ~PacManSystem();
	void initSystem() override;
	void update() override;
	void resetPacman();
	void recieve(const Message& m) override;
private:

	void stopOnBorders();
	void pacmanInput();
	void handleMessages();

	Transform *_pmTR;
};

