#pragma once
#include "GameState.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"
#include <SDL.h>
#include <vector>

class RunningState : public GameState
{
public:
	RunningState(FighterFacade* f, AsteroidsFacade* a);
	virtual ~RunningState() {}
	void enter() override { std::cout << "Entered RUNNINGSTATE" << std::endl; }
	void leave() override { std::cout << "Exited RUNNINGSTATE" << std::endl; }
	void update() override;

private:
	ecs::Manager* _mngr;
	FighterFacade* _fUtils;
	AsteroidsFacade* _aUtils;

	void checkCollisions();

	Uint32 _lastAsteroidAdded;

	const std::vector<entity_t>& _asteroids;
};


