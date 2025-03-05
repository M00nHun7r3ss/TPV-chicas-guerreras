#pragma once

#include "../ecs/Manager.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"
#include "Game.h"
class GameState {
public:
	GameState() : _mngr(Game::Instance()->getManager()) {}
	virtual ~GameState() {}
	virtual void enter() = 0;
	virtual void leave() = 0;
	virtual void update() = 0;

protected:
	ecs::Manager* _mngr;
	FighterUtils* _fUtils;
	AsteroidsUtils* _aUtils;
};