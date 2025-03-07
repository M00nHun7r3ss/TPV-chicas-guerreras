#include "GameOverState.h"

void GameOverState::enter()
{
	if (_aUtils->getAsteroidNumber() == 0)
	{
		// CHAMPION.
		_mode = true; 
	}
	else
	{
		// LOOSER.
		_mode = false;
	}
}

void GameOverState::update()
{
	std::string text;

	if (_mode)
	{
		text = "Game Over Loser! Press ENTER to continue.";
	}
	else
	{
		text = "Game Over Champion! Press ENTER to continue.";
	}

	// --- Text.
	Texture startTex(sdlutils().renderer(), text,
		sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x444444ff));

	SDL_Rect dest = build_sdlrect( //
		(sdlutils().width() - startTex.width()) / 2.0f, //
		sdlutils().height() - startTex.height() / 2.0f, //
		startTex.width(), //
		startTex.height());

	startTex.render(dest);

	// --- Input.
	InputHandler& ihldr = ih();

	// ya sea por clic o por tecla...
	if (ihldr.mouseButtonDownEvent() || ihldr.keyDownEvent()) {
		// !!! cambia a NewGameState
		Game::Instance()->setState(Game::NEWGAME);
	}
}
