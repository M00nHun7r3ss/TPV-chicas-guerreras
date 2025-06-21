#pragma once
#include "PacmanState.h"

class WalkingState : public PacmanState {
public:
	WalkingState();
	virtual ~WalkingState();
	void enter(PacmanWS& o) override;
	void handleInput(PacmanWS& o) override;
	void update(PacmanWS& o) override;

private:
	Vector2D _pos;
	Vector2D _vel;
	float _width;
	float _height;
};

