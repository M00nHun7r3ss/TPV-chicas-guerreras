#pragma once
#include "GameState.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"
#include <SDL.h>

class RunningState : public GameState
{
public:
	RunningState() : _lastAsteroidAdded(0) {};
	virtual ~RunningState() {}
	void enter() override;
	void leave() override;
	void update() override;

private:
	FighterUtils* _fUtils;
	AsteroidsUtils* _aUtils;
	Game* _g = Game::Instance();

	void checkCollisions();

	Uint32 _lastAsteroidAdded;
};


