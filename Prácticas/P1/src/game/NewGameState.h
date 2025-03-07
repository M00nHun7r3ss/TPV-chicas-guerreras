#pragma once
#include "GameState.h"
#include "FighterUtils.h"

class NewGameState : public GameState
{
public:
	NewGameState() = default;
	virtual ~NewGameState() {}
	void enter() override {}
	void leave() override {}
	void update() override;

private:
	FighterUtils* _fUtils = new FighterUtils();
};

