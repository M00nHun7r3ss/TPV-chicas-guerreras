#pragma once
#include "GameState.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"
#include <SDL.h>

class RunningState : public GameState
{
public:
	RunningState() : _mngr(Game::Instance()->getManager()), _lastAsteroidAdded(0) {};
	virtual ~RunningState() {}
	void enter() override {}
	void leave() override {}
	void update() override;

private:
	ecs::Manager* _mngr;
	FighterUtils* _fUtils;
	AsteroidsUtils* _aUtils;

	void checkCollisions();

	Uint32 _lastAsteroidAdded;
};


