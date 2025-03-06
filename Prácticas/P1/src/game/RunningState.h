#pragma once
#include "GameState.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"

class RunningState : public GameState
{
public:
	RunningState() = default;
	virtual ~RunningState() {}
	void enter() override;
	void leave() override;
	void update() override;

private:
	FighterUtils* _fUtils;
	AsteroidsUtils* _aUtils;
	Game* _g = Game::Instance();

};


