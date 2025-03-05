#pragma once
#include "GameState.h"

class NewGameState : public GameState
{
public:
	NewGameState() = default;
	virtual ~NewGameState() {}
	void enter() override;
	void leave() override;
	void update() override;

};

