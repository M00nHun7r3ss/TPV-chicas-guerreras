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
	GameOverState(AsteroidsFacade* a);
	virtual ~GameOverState() {}
	void enter() override;
	void leave() override;
	void update() override;

private:
	AsteroidsFacade* _aUtils;
	bool _mode; // false -> LOOSER; true -> CHAMPION
};

