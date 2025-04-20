#include "GameOverState.h"

#include "Game.h"
#include "../ecs/Manager.h"
#include "../systems/FoodSystem.h"
#include "../systems/PacManSystem.h"

void GameOverState::enter()
{
	ecs::Manager* mngr = Game::Instance()->getManager();
	sdlutils().musics().at("pacman_chomp").pauseMusic();

	if (mngr->getSystem<FoodSystem>()->getCurrentFruits() == 0)
	{
		// CHAMPION.
		_message = &sdlutils().msgs().at("gameovergood");
		sdlutils().soundEffects().at("pacman_won").play(0, 1);
	}
	else if (mngr->getSystem<PacManSystem>()->getPacmanHealth() == 0)
	{
		// LOOSER.
		_message = &sdlutils().msgs().at("gameoverbad");
		//Sonido pacman muerte
		sdlutils().soundEffects().at("pacman_death").play(0, 1);
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