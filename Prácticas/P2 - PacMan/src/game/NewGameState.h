#pragma once

#include <SDL_rect.h>

#include "../sdlutils/SDLUtils.h"

#include "../ecs/messages.h"

#include "Game.h"

#include "GameState.h"

namespace ecs
{
	class Manager;
}

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
	ecs::Manager* _mngr;
};
