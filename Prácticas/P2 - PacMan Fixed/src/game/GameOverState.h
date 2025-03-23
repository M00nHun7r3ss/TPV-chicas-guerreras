#pragma once
#include "GameState.h"

#include <SDL_rect.h>

#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

class GameOverState : public GameState
{
public:
    GameOverState();
    virtual ~GameOverState() {}
    void enter() override;
    void leave() override {}
    void update() override;

private:

    Texture* _message;
    SDL_Rect _dest;
};