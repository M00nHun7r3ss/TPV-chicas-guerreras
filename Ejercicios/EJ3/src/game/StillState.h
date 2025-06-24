#pragma once
#include "../utils/Vector2D.h"
#include "PacmanState.h"

class StillState : public PacmanState {
public:
	StillState() : _vel(), _rot() {}
	virtual ~StillState() {}
	void enter(PacmanWS& o) override;
	void handleInput(PacmanWS& o) override;
	void update(PacmanWS& o) override;

private:
	Vector2D _vel;
	float _rot;
};

