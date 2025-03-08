#include "PausedState.h"

void PausedState::enter()
{
	std::cout << "Entered PAUSESTATE" << std::endl;
	sdlutils().virtualTimer().pause();
	_message = &sdlutils().msgs().at("PausedState");

}

void PausedState::leave()
{
	std::cout << "Exited PAUSESTATE" << std::endl;
	sdlutils().virtualTimer().resume();
}

void PausedState::update()
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

		// !!! cambia a RunningState
		Game::Instance()->setState(Game::RUNNING);
	}
}
