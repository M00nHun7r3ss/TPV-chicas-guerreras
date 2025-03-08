#include "NewRoundState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

NewRoundState::NewRoundState(FighterFacade* f, AsteroidsFacade* a)
	: _fUtils(f),
	  _aUtils(a)
{
}

void NewRoundState::enter()
{
	std::cout << "Entered NEWROUNDSTATE" << std::endl;

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
	if (ihldr.isKeyDown(SDL_SCANCODE_0)) { // !!! cambiar.
		_fUtils->reset_fighter();
		_aUtils->remove_all_asteroids();
		_aUtils->create_asteroids(1);

		// !!! cambia a RunningState
		Game::Instance()->setState(Game::RUNNING);
	}
}
