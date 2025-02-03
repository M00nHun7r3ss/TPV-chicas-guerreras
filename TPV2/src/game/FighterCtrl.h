#pragma once
#include "InputComponent.h"

#include <SDL.h>

class FighterCtrl : public InputComponent
{
public:
	FighterCtrl();
	virtual ~FighterCtrl();
	void handleInput(Container* o) override;
	inline void setKeys(SDL_Scancode left, SDL_Scancode right) {
		_left = left;
		_right = right;
	}
	
private:
	SDL_Scancode _left;
	SDL_Scancode _right;
	float _rot;
};

