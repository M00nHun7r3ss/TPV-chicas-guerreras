#pragma once

#include <SDL_rect.h>

#include "../sdlutils/SDLUtils.h"

#include "GameState.h"

class NewGameState : public GameState
{
public:
	NewGameState();
	virtual ~NewGameState() {}
	void enter() override;
	void leave() override {}
	void update() override;

private:
	Texture* _message;
	SDL_Rect _dest;
};
