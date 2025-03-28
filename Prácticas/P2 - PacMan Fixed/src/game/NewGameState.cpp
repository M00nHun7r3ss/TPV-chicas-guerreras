#include "NewGameState.h"

#include "../ecs/Manager.h"

void NewGameState::enter()
{
	_message = &sdlutils().msgs().at("newgame");
}

void NewGameState::update()
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

		//Envia mensaje de que ha empezado juego
		Message m;
		m.id = _m_NEW_GAME;
		Game::Instance()->getManager()->send(m);

		// !!! cambia a NewRoundState
		Game::Instance()->setState(Game::NEWROUND);

	}

}

