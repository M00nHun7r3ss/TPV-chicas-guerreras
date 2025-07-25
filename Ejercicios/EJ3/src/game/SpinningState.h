#pragma once
#include "PacmanState.h"

class SpinningState : public PacmanState {
public:
	SpinningState(): _deg() {}
	virtual ~SpinningState() {}
	void enter(PacmanWS& o) override;
	void handleInput(PacmanWS& o) override;
	void update(PacmanWS& o) override;

private:
	float _deg;
};

