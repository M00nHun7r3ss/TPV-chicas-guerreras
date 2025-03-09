#pragma once

#include <SDL_rect.h>

#include "../sdlutils/SDLUtils.h"

#include "GameState.h"
#include "FighterUtils.h"

class NewGameState : public GameState
{
public:
	NewGameState(FighterFacade* f);
	virtual ~NewGameState() {}
	void enter() override;
	void leave() override {}
	void update() override;

private:
	FighterFacade* _fUtils;
	Texture* _message;
	SDL_Rect _dest;
};

