#pragma once
#include "GameState.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "AsteroidsUtils.h"
#include <string>

class GameOverState : public GameState
{
public:
	GameOverState() = default;
	virtual ~GameOverState() {}
	void enter() override;
	void leave() override {}
	void update() override;

private:
	AsteroidsUtils* _aUtils;
	bool _mode; // false -> LOOSER; true -> CHAMPION
};

