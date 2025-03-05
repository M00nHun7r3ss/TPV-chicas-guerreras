#pragma once
#include "GameState.h"

class NewRoundState : public GameState
{
public:
	NewRoundState() = default;
	virtual ~NewRoundState() {}
	void enter() override;
	void leave() override;
	void update() override;

};


