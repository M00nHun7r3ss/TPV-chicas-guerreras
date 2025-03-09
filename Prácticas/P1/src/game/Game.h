// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../utils/Singleton.h"

#include "FighterFacade.h"
#include "GameState.h"

namespace ecs {
class Manager;
}

class Game : public Singleton<Game> {
	friend Singleton;
public:
	enum State {RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER};

	Game();
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
private:

	ecs::Manager *_mngr;

	GameState* _state;
	GameState* _paused_state;
	GameState* _running_state;
	GameState* _newgame_state;
	GameState* _newround_state;
	GameState* _gameover_state;
};

