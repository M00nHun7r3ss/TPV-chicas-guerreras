#pragma once
class PacmanWS;

class PacmanState {
public:
	PacmanState() {}
	virtual ~PacmanState() {}
	virtual void enter(PacmanWS& o) = 0;
	virtual void handleInput(PacmanWS& o) = 0;
	virtual void update(PacmanWS& o) = 0;
};