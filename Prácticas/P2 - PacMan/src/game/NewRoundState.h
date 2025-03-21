#pragma once
#include "GameState.h"

#include <SDL_rect.h>

#include "../sdlutils/SDLUtils.h"


class NewRoundState : public GameState
{
public:
	NewRoundState();
	virtual ~NewRoundState() {}
	void enter() override;
	void leave() override {}
	void update() override;

private:
	Texture* _message;
	SDL_Rect _dest;

};
