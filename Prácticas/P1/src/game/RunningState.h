#pragma once
#include "GameState.h"

class RunningState : public GameState
{
public:
	RunningState() = default;
	virtual ~RunningState() {}
	void enter() override;
	void leave() override;
	void update() override;

};


