// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/DeAcceleration.h"
#include "../components/FighterCtrl.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Health.h"
#include "../components/Gun.h"

#include "AsteroidsUtils.h"
#include "NewGameState.h"
#include "NewRoundState.h"
#include "RunningState.h"
#include "GameState.h"

using ecs::Manager;

Game::Game() :
		_mngr(nullptr) {
}

Game::~Game() {
	delete _mngr;

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();
}

bool Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("Asteroids", 800, 600,
			"resources/config/asteroid.resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return false;
	}

	// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
				<< std::endl;
		return false;

	}

	return true;
}

void Game::initGame()
{


	// create the game info entity
	 //ecs::entity_t ginfo = _mngr->addEntity();
	//_mngr->setHandler(ecs::hdlr::GAMEINFO, ginfo);
	//_mngr->addComponent<AsteroidsUtils>(ginfo, tf);

	// Create the manager
	_mngr = new Manager();

	_state = nullptr;
	_paused_state = nullptr;
	_running_state = nullptr;
	_newgame_state = nullptr;
	_newround_state = nullptr;
	_gameover_state = nullptr;
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	// --- NOTA : El primero (sdlutils() métodos de tiempo) está basado en tiempo real, el segundo (sdlutils().virtualTimer()) es un objeto que nos permite pausar y reanudar el tiempo (para el pause).

	// reset the time before starting - so we calculate correct delta-time in the first iteration
	sdlutils().virtualTimer().resetTime();

	while (!exit) {
		// store the current time -- all game objects should use this time when
		// then need to the current time. They also have accessed to the time elapsed
		// between the last two calls to regCurrTime().
		Uint32 startTime = sdlutils().virtualTimer().regCurrTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		_state->update();

		////¿Esto hace falta?
		//_mngr->update();
		//_mngr->refresh();

		//checkCollisions();

		//sdlutils().clearRenderer();
		//_mngr->render();
		//sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().virtualTimer().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

	refresh();

}

void Game::refresh()
{
}

void Game::checkCollisions() {

	// the fighters Transform
	auto fighter = _mngr->getHandler(ecs::hdlr::FIGHTER);
	auto playerTF = _mngr->getComponent<Transform>(fighter);

	// the GameCtrl component
	auto ginfo = _mngr->getHandler(ecs::hdlr::GAMEINFO);
	//auto gctrl = _mngr->getComponent<GameCtrl>(ginfo);

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	auto &asteroids = _mngr->getEntities(ecs::grp::ASTEROIDS);
	auto n = asteroids.size();
	for (auto i = 0u; i < n; i++) {
		auto e = asteroids[i];
		if (_mngr->isAlive(e)) { // if the star is active (it might have died in this frame)

			// the Asteroids's Transform
			//
			auto eTR = _mngr->getComponent<Transform>(e);

			// check if PacMan collides with the Star (i.e., eat it)
			if (Collisions::collides(playerTF->getPos(), playerTF->getWidth(),
				playerTF->getHeight(), //
					eTR->getPos(), eTR->getWidth(), eTR->getHeight())) {
				_mngr->setAlive(e, false);
				//gctrl->onAsteroidDestroyed();

				// play sound on channel 1 (if there is something playing there
				// it will be cancelled
				//sdlutils().soundEffects().at("pacman_eat").play(0, 1);
			}
		}
	}
}
