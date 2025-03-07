#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

class PausedState : public GameState
{
public:
	PausedState() = default;
	virtual ~PausedState() {}
	void enter() override;
	void leave() override;
	void update() override;
};


