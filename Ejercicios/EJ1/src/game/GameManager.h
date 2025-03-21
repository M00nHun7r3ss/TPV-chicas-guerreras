// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <array>

#include "Container.h"

class GameManager: public Container {
public:

	enum Side {
		LEFT = 0, //
		RIGHT
	};

	enum GameState {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER // game over
	};

	GameManager(GameObject *b);
	virtual ~GameManager();

	inline GameState getState() {
		return _state;
	}

	inline void setState(GameState state) {
		_state = state;
	}

	inline void setScore(std::size_t player, unsigned int score) {
		_score[player] = score;
	}

	inline unsigned int getScore(std::size_t player) {
		return _score[player];
	}

	void onBallExit(Side side);
	void resetBall();
	void moveBall();

private:
	std::array<unsigned int, 2> _score;
	GameState _state;
	const unsigned int _maxScore;
	GameObject *_ball;
};

