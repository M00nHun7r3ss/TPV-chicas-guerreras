#include "NewRoundState.h"

#include "../ecs/Manager.h"

void NewRoundState::enter()
{
	_message = &sdlutils().msgs().at("newround");
}

void NewRoundState::update()
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

	// si el enter es presionado...
	if (ihldr.isKeyDown(SDL_SCANCODE_RETURN)) {

		//Envia mensaje de que ha empezado ronda
		Message m;
		m.id = _m_ROUND_START;
		Game::Instance()->getManager()->send(m);

		// !!! cambia a RunningState
		Game::Instance()->setState(Game::RUNNING);
	}
}