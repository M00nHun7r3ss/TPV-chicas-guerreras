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

private:

	// --- Systems.
	ecs::System* _pacmanSys;
	ecs::System* _gameCtrlSys;
	ecs::System* _startsSys;
	ecs::System* _renderSys;
	ecs::System* _collisionSys;
};
