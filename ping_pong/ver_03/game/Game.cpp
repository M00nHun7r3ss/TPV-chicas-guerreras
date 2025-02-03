// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "Ball.h"
#include "BallWithImage.h"
#include "Paddle.h"
#include "GameManager.h"
#include "PaddleNoFill.h"
#include "PaddleWithAI.h"
#include "PaddleWithMouse.h"

Game::Game() :
		_gm(nullptr), //
		_leftPaddle(nullptr), //
		_rightPaddle(nullptr), //
		_ball(nullptr) {
}

Game::~Game() {
	// delete all game objects
	for (GameObject *o : _objs) {
		delete o;
	}

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();
}

void Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("Ping Pong", 800, 600,
			"resources/config/pingpong.resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return;
	}

	// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
				<< std::endl;
		return;

	}

	// the ball
	//_ball = new Ball();
	_ball = new BallWithImage(&sdlutils().images().at("tennis_ball"));
	_ball->setWidth(10.0f);
	_ball->setHeight(10.0f);
	_ball->getPos().set(sdlutils().width() / 2 - 5,
			sdlutils().height() / 2 - 5);

	// the left paddle
	//_leftPaddle = new Paddle(build_sdlcolor(0xff0000ff));
	_leftPaddle = new PaddleNoFill(build_sdlcolor(0xff0000ff));
	//_leftPaddle = new PaddleWithMouse(build_sdlcolor(0xff0000ff));
	//_leftPaddle = new PaddleWithAI(build_sdlcolor(0xff0000ff), ball);
	_leftPaddle->setWidth(10.0f);
	_leftPaddle->setHeight(50.0f);
	_leftPaddle->getPos().set(10, sdlutils().height() / 2 - 25);
	_leftPaddle->setKeys(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A);

	// the right paddle
//	_rightPaddle = new Paddle(build_sdlcolor(0x0000ffff));
//	_rightPaddle = new PaddleNoFill(build_sdlcolor(0x0000ffff));
//	_rightPaddle = new PaddleWithMouse(build_sdlcolor(0x0000ffff));
	_rightPaddle = new PaddleWithAI(build_sdlcolor(0x0000ffff), _ball);
	_rightPaddle->setWidth(10.0f);
	_rightPaddle->setHeight(50.0f);
	_rightPaddle->getPos().set(sdlutils().width() - 15,
			sdlutils().height() / 2 - 25);
//	rightPaddle->setKeys(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT);

	_gm = new GameManager(_ball);

	// add them all to the list of game objects
	_objs.push_back(_ball);
	_objs.push_back(_leftPaddle);
	_objs.push_back(_rightPaddle);
	_objs.push_back(_gm);

}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {

		// store the current time -- all game objects should use this time when
		// then need to the current time. They also have accessed to the time elapsed
		// between the last two calls to regCurrTime().
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		for (auto &o : _objs) {
			o->handleInput();
		}

		// update
		for (auto &o : _objs) {
			o->update();
		}

		checkCollisions();

		sdlutils().clearRenderer();

		// render
		for (auto &o : _objs) {
			o->render();
		}

		sdlutils().presentRenderer();
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

void Game::checkCollisions() {
	if (_gm->getState() != GameManager::RUNNING)
		return;

	// check if ball hits paddles
	if (Collisions::collides(_leftPaddle->getPos(), _leftPaddle->getWidth(),
			_leftPaddle->getHeight(), _ball->getPos(), _ball->getWidth(),
			_ball->getHeight())
			|| Collisions::collides(_rightPaddle->getPos(),
					_rightPaddle->getWidth(), _rightPaddle->getHeight(),
					_ball->getPos(), _ball->getWidth(), _ball->getHeight())) {

		// change the direction of the ball, and increment the speed
		auto &vel = _ball->getVel();// the use of & is important, so the changes goes directly to the ball
		vel.setX(-vel.getX());
		vel = vel * 1.2f;

		// play some sound
		sdlutils().soundEffects().at("paddle_hit").play();
	} else if (_ball->getPos().getX() < 0)
		_gm->onBallExit(GameManager::LEFT);
	else if (_ball->getPos().getX() + _ball->getWidth() > sdlutils().width())
		_gm->onBallExit(GameManager::RIGHT);
}

