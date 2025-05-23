#include "GameOverState.h"

GameOverState::GameOverState(AsteroidsFacade* a)
	: _aUtils(a)
{
}

void GameOverState::enter()
{
	if (_aUtils->getAsteroidNumber() == 0)
	{
		// CHAMPION.
		_message = &sdlutils().msgs().at("GameOverGood");
	}
	else
	{
		// LOOSER.
		_message = &sdlutils().msgs().at("GameOverBad");
	}
}

void GameOverState::update()
{
	// --- Message
	_dest = build_sdlrect( 
		(sdlutils().width() - _message->width()) / 2.0f, 
		(sdlutils().height() - _message->height()) / 2.0f, 
		_message->width(), 
		_message->height());

	sdlutils().clearRenderer();
	_message->render(_dest);
	sdlutils().presentRenderer();

	// --- Input.
	InputHandler& ihldr = ih();

	// ya sea por clic o por tecla...
	if (ihldr.mouseButtonDownEvent() || ihldr.keyDownEvent()) {
		// !!! cambia a NewGameState
		Game::Instance()->setState(Game::NEWGAME);
	}
}
