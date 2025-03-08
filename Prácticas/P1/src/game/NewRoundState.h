#pragma once
#include "GameState.h"
#include "FighterUtils.h"
#include "AsteroidsUtils.h"

class NewRoundState : public GameState
{
public:
	NewRoundState(FighterFacade* f, AsteroidsFacade* a);
	virtual ~NewRoundState() {}
	void enter() override { std::cout << "Entered NEWROUNDSTATE" << std::endl; }
	void leave() override { std::cout << "Exited NEWROUNDSTATE" << std::endl; }
	void update() override;

private:
	FighterFacade* _fUtils;
	AsteroidsFacade* _aUtils;

};


