#pragma once
#include "GameState.h"

#include <SDL_rect.h>
#include <string>

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "Game.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"

class NewRoundState : public GameState
{
public:
	NewRoundState(FighterFacade* f, AsteroidsFacade* a);
	virtual ~NewRoundState() {}
	void enter() override;
	void leave() override { std::cout << "Exited NEWROUNDSTATE" << std::endl; }
	void update() override;

private:
	FighterFacade* _fUtils;
	AsteroidsFacade* _aUtils;
	Texture* _message;
	SDL_Rect _dest;

};


