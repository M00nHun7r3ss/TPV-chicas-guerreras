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
#include "PausedState.h"
#include "GameOverState.h"
#include "GameState.h"


using ecs::Manager;

Game::Game() :
		_mngr(new Manager()), 
		_newgame_state(nullptr), 
		_newround_state(nullptr),
		_paused_state(nullptr), 
		_running_state(nullptr), 
		_gameover_state(nullptr){
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

	// Inizialize and declare facades.
	AsteroidsFacade* ast_facade = new AsteroidsUtils();
	FighterFacade* fighter_facade = new FighterUtils();

	// Inizialize states
	_newgame_state = new NewGameState(fighter_facade);
	_newround_state = new NewRoundState(fighter_facade, ast_facade);
	_paused_state = new PausedState();
	_running_state = new RunningState(fighter_facade, ast_facade);
	_gameover_state = new GameOverState(ast_facade);

	fighter_facade->create_fighter();

	_state = _newgame_state;

	_state->enter();
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

		//Esto es para que renderice
		_mngr->update();
		_mngr->refresh();

		if (_state == _running_state)
		{
			sdlutils().clearRenderer();
			_mngr->render();
			sdlutils().presentRenderer();
		}
		else
		{
			_mngr->render();
		}

		Uint32 frameTime = sdlutils().virtualTimer().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

	refresh();

}

void Game::refresh()
{
}

