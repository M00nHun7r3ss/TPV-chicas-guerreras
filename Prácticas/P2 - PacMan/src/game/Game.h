// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../utils/Singleton.h"

#include <vector>

#include "GameState.h"
#include "../ecs/ecs.h"

namespace ecs{
	class Manager;
}

class Game : public Singleton<Game> {
			friend Singleton;
public:

	enum State { RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER };

	//enum System { PACMAN, GAMECTRL, GHOST, RENDER, COLLISIONS};

	//Game();
	virtual ~Game();
	bool init();
	void initGame();
	void start();

	inline ecs::Manager* getManager() { return _mngr; }

	inline void setState(State s) {

		_state->leave();
		switch (s) {
		case RUNNING:
			_state = _running_state;
			break;
		case PAUSED:
			_state = _paused_state;
			break;
		case NEWGAME:
			_state = _newgame_state;
			break;
		case NEWROUND:
			_state = _newround_state;
			break;
		case GAMEOVER:
			_state = _gameover_state;
			break;
		default:
			break;
		}
		_state->enter();
	}

	//Getters systems
	ecs::System* pacmanSys() { return _pacmanSys; }
	ecs::System* gameCtrlSys() { return _gameCtrlSys; }
	ecs::System* ghostSys() { return _ghostSys; }
	ecs::System* renderSys() { return _renderSys; }
	ecs::System* collisionSys() { return _collisionSys; }

private:

	Game();

	ecs::Manager* _mngr;

	// --- Systems.
	ecs::System *_pacmanSys;
	ecs::System *_gameCtrlSys;
	ecs::System *_ghostSys;
	ecs::System *_renderSys;
	ecs::System *_collisionSys;

	// --- States.
	GameState* _state;
	GameState* _running_state;
	GameState* _paused_state;
	GameState* _newgame_state;
	GameState* _newround_state;
	GameState* _gameover_state;
};

