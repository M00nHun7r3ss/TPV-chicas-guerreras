#include "PausedState.h"

void PausedState::enter()
{
	std::cout << "Entered PAUSESTATE" << std::endl;
	sdlutils().virtualTimer().pause();

}

void PausedState::leave()
{
	std::cout << "Exited PAUSESTATE" << std::endl;
	sdlutils().virtualTimer().resume();
}

void PausedState::update()
{
	// --- Text.
	Texture startTex(sdlutils().renderer(), "Press any key to resume the game",
		sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x444444ff));

	SDL_Rect dest = build_sdlrect( 
		(sdlutils().width() - startTex.width()) / 2.0f, 
		sdlutils().height() - startTex.height() / 2.0f, 
		startTex.width(), 
		startTex.height());

	startTex.render(dest);

	// --- Input.
	InputHandler& ihldr = ih();

	// ya sea por clic o por tecla...
	if (ihldr.mouseButtonDownEvent() || ihldr.keyDownEvent()) {

		// !!! cambia a RunningState
		Game::Instance()->setState(Game::RUNNING);
	}
}
