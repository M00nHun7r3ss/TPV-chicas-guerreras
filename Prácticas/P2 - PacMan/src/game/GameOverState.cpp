#include "GameOverState.h"

#include "Game.h"

void GameOverState::enter()
{
	_message = &sdlutils().msgs().at("gameover");

	//if (_aUtils->getAsteroidNumber() == 0)
	//{
	//	// CHAMPION.
		//_message = &sdlutils().msgs().at("gameovergood");
	//}
	//else
	//{
	//	// LOOSER.
	//	_message = &sdlutils().msgs().at("gameoverbad");
	//}
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