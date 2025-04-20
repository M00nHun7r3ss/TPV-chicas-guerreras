#pragma once
#include "GameState.h"

#include "Game.h"

#include <SDL_rect.h>

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

class PausedState : public GameState
{
public:
	PausedState() = default;
	virtual ~PausedState() {}
	void enter() override;
	void leave() override;
	void update() override;

private:
	Texture* _message;
	SDL_Rect _dest;
};


