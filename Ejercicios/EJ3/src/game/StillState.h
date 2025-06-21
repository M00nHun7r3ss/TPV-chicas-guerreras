#pragma once
#include "PacmanState.h"

class StillState : public PacmanState {
public:
	StillState(Vector2D vel, float rot) : _vel(vel), _rot(rot) {}
	virtual ~StillState() {}
	void enter(PacmanWS& o) override;
	void handleInput(PacmanWS& o) override;
	void update(PacmanWS& o) override;

private:
	Vector2D _vel;
	float _rot;
};

