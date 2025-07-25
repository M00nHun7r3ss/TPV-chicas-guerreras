// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
//Systems
#include "../systems/CollisionsSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/FoodSystem.h"
#include "../systems/ImmunitySystem.h"
#include "../systems/ShieldSystem.h"
//Scenes
#include "GameState.h"
#include "NewGameState.h"
#include "NewRoundState.h"
#include "PauseState.h"
#include "RunningState.h"
#include "GameOverState.h"

using ecs::Manager;

Game::Game() :
		_mngr(), 
		_pacmanSys(), 
		_ghostSys(), 
		_renderSys(), 
		_collisionSys(),
		_foodSys(),
		_immunitySys(),
		_shieldSys()
{

}

Game::~Game() {
	delete _mngr;

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();

	// delete states. do not delete _state.
	// delete in inverse order.
	delete _gameover_state;
	delete _newround_state;
	delete _newgame_state;
	delete _paused_state;
	delete _running_state;
}

bool Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("PacMan", 800, 600,
			"resources/config/resources.json")) {

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
	// Create the manager
	_mngr = new Manager();

	// add the systems
	_pacmanSys = _mngr->addSystem<PacManSystem>();
	_ghostSys = _mngr->addSystem<GhostSystem>();
	_renderSys = _mngr->addSystem<RenderSystem>();
	_collisionSys = _mngr->addSystem<CollisionsSystem>();
	_foodSys = _mngr->addSystem<FoodSystem>();
	_immunitySys = _mngr->addSystem<ImmunitySystem>();
	_shieldSys = _mngr->addSystem<ShieldSystem>();

	// add the states
	_running_state = new RunningState();
	_paused_state = new PauseState();
	_newgame_state = new NewGameState();
	_newround_state = new NewRoundState();
	_gameover_state = new GameOverState();

	// inicia a estado NewGame
	setState(NEWGAME); //NEWGAME
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		//Actualizamos el estado
		_state->update();

		_mngr->refresh();

		//�Borra mensajes pendientes?
		_mngr->flushMessages();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

