#pragma once
#include "../utils/Vector2D.h"
#include "PacmanState.h"

class StillState : public PacmanState {
public:
	StillState() {}
	virtual ~StillState() {}
	void enter(PacmanWS& o) override;
	void handleInput(PacmanWS& o) override;
	void update(PacmanWS& o) override;

};

