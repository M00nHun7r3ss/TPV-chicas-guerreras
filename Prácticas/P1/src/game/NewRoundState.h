#pragma once
#include "GameState.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"

class NewRoundState : public GameState
{
public:
	NewRoundState() = default;
	virtual ~NewRoundState() {}
	void enter() override;
	void leave() override;
	void update() override;

private:
	FighterUtils* _fUtils;
	AsteroidsUtils* _aUtils;

};


