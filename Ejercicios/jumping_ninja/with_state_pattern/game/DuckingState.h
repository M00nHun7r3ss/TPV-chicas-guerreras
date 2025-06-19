// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "NinjaState.h"

class DuckingState: public NinjaState {
public:
	DuckingState();
	virtual ~DuckingState();
	void enter(NinjaWS &o) override;
	void handleInput(NinjaWS &o) override;
	void update(NinjaWS &o) override;
private:
	float _charge;
};

