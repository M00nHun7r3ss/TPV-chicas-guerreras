#pragma once
#include "../utils/Vector2D.h"
#include "PacmanState.h"

class WalkingState : public PacmanState {
public:
	WalkingState() {}
	virtual ~WalkingState() {}
	void enter(PacmanWS& o) override;
	void handleInput(PacmanWS& o) override;
	void update(PacmanWS& o) override;

};

