#include "RunningState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

void RunningState::update()
{
	bool exit = false;
	// Si hay 0 asteroides cambia al estado GameOverState y sale del metodo.
	if (_aUtils->getAsteroidNumber() == 0 && !exit) {
		_g->setState(Game::GAMEOVER);
		exit = true;
	}

	// Si el usuario pulsa la tecla P cambia al estado PauseState y sale del metodo.
	InputHandler& ihldr = ih();
	if (ihldr.keyDownEvent() && ihldr.isKeyDown(SDLK_p) && !exit) {
		_g->setState(Game::PAUSED);
		exit = true;
	}
}
