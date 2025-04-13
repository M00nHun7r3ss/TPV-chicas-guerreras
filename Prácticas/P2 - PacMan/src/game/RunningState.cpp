#include "RunningState.h"

#include "../ecs/Manager.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include <vector>

#include "../game/Game.h"

#include "../components/Transform.h"

RunningState::RunningState()
{
}

void RunningState::update()
{
	bool exit = false;

	// Si el usuario pulsa la tecla P cambia al estado PauseState y sale del metodo.
	InputHandler& ihldr = ih();
	if (ihldr.keyDownEvent() && ihldr.isKeyDown(SDLK_p) && !exit) {
		Game::Instance()->setState(Game::PAUSED);
		
		exit = true;
	}

	// Update de cada sistema
	Game::Instance()->ghostSys()->update();
	Game::Instance()->pacmanSys()->update();
	Game::Instance()->collisionSys()->update();
	Game::Instance()->foodSys()->update();
	Game::Instance()->immunitySys()->update();

	//Si no va aquí, llevar al game, cuando se llame al update de RunningState -> preguntar a Samir
	sdlutils().clearRenderer();
	Game::Instance()->renderSys()->update();
	sdlutils().presentRenderer();

}
