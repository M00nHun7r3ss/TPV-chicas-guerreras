#pragma once
#include "GameState.h"

#include "../ecs/ecs.h"

#include <SDL.h>
#include <vector>

class RunningState : public GameState
{
public:
	RunningState();
	virtual ~RunningState() {}
	void enter() override {}
	void leave() override {}
	void update() override;
};
