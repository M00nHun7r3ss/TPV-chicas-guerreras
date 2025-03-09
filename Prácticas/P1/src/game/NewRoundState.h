#pragma once
#include "GameState.h"

#include <SDL_rect.h>

#include "../sdlutils/SDLUtils.h"

#include "FighterUtils.h"
#include "AsteroidsUtils.h"

class NewRoundState : public GameState
{
public:
	NewRoundState(FighterFacade* f, AsteroidsFacade* a);
	virtual ~NewRoundState() {}
	void enter() override;
	void leave() override {}
	void update() override;

private:
	FighterFacade* _fUtils;
	AsteroidsFacade* _aUtils;
	Texture* _message;
	SDL_Rect _dest;

};


