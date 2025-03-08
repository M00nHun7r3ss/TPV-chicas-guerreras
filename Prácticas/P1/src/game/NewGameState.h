#pragma once

#include <SDL_rect.h>
#include <string>

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "GameState.h"
#include "FighterUtils.h"

class NewGameState : public GameState
{
public:
	NewGameState(FighterFacade* f);
	virtual ~NewGameState() {}
	void enter() override;
	void leave() override { std::cout << "Exited NEWGAMEGSTATE" << std::endl; }
	void update() override;

private:
	FighterFacade* _fUtils;
	Texture* _message;
	SDL_Rect _dest;
};

