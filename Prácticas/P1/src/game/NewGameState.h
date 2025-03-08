#pragma once
#include "GameState.h"
#include "FighterUtils.h"

class NewGameState : public GameState
{
public:
	NewGameState(FighterFacade* f);
	virtual ~NewGameState() {}
	void enter() override { std::cout << "Entered NEWGAMESTATE" << std::endl; }
	void leave() override { std::cout << "Exited NEWGAMEGSTATE" << std::endl; }
	void update() override;

private:
	FighterFacade* _fUtils;
};

