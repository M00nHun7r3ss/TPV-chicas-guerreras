#pragma once
#include "GameState.h"

#include <SDL_rect.h>

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

class PauseState : public GameState
{
public:
	PauseState() = default;
	virtual ~PauseState() {}
	void enter() override;
	void leave() override;
	void update() override;

private:
	Texture* _message;
	SDL_Rect _dest;
};


