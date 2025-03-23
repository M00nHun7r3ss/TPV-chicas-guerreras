#include "NewGameState.h"

//#include "Game.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

NewGameState::NewGameState()
{
}

void NewGameState::enter()
{
	_message = &sdlutils().msgs().at("NewGameState");
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
		//m.id = _m_NEW_GAME;
		_mngr->send(m);


		// !!! cambia a NewRoundState
		//Game::Instance()->setState(Game::NEWROUND);

	}

}

