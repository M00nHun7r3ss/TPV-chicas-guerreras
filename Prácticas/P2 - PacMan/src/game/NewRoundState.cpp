#include "NewRoundState.h"

#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

NewRoundState::NewRoundState()
{
}

void NewRoundState::enter()
{
	_message = &sdlutils().msgs().at("NewRoundState");
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

		// !!! cambia a RunningState
		Game::Instance()->setState(Game::RUNNING);
	}
}