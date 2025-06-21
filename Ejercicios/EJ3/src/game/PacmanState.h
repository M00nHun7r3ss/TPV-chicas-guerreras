#pragma once
#include "../utils/Vector2D.h"

class PacmanWS;

class PacmanState {
public:
	virtual ~PacmanState() {
	}
	virtual void enter(PacmanWS& o) = 0;
	virtual void handleInput(PacmanWS& o) = 0;
	virtual void update(PacmanWS& o) = 0;
};