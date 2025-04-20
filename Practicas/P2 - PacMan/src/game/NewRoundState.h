#pragma once
#include "GameState.h"

#include "Game.h"

#include <SDL_rect.h>

#include "../ecs/messages.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

class NewRoundState : public GameState
{
public:
	NewRoundState() = default;
	virtual ~NewRoundState() {}
	void enter() override;
	void leave() override {}
	void update() override;

private:
	Texture* _message;
	SDL_Rect _dest;
};
