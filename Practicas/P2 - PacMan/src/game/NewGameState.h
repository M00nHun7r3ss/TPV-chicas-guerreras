#pragma once
#include "GameState.h"

#include "Game.h"

#include <SDL_rect.h>

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/messages.h"

class NewGameState : public GameState
{
public:
	NewGameState() = default;
	virtual ~NewGameState() {}
	void enter() override;
	void leave() override {}
	void update() override;

private:
	Texture* _message;
	SDL_Rect _dest;
};
