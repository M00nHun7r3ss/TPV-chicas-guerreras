#pragma once
#include "GameState.h"

#include <SDL_rect.h>

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "AsteroidsUtils.h"

class GameOverState : public GameState
{
public:
	GameOverState(AsteroidsFacade* a);
	virtual ~GameOverState() {}
	void enter() override;
	void leave() override {}
	void update() override;

private:
	AsteroidsFacade* _aUtils;
    Texture* _message;
    SDL_Rect _dest;
};