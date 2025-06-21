#include "PacmanWS.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

#include "SpinningState.h"
#include "StillState.h"
#include "WalkingState.h"


PacmanWS::PacmanWS() :
	_img(),
	_state(), 
	_spinning_state(),
	_still_state(),
	_walking_state()
{
	_width = 100;
	_height = 100;
	float x = (sdlutils().width() - _width) / 2;
	float y = sdlutils().height() - _height;
	_pos.set(x, y);
	
	_spinning_state = new SpinningState(_rot, 0.0);
	_still_state = new StillState(_vel, _rot);
	_walking_state = new WalkingState(_pos, _vel, _width, _height);

	_state = _still_state;
	_state->enter(*this);
}

PacmanWS::~PacmanWS() {
}

void PacmanWS::update() {
	_state->update(*this);
}

void PacmanWS::handleInput() {
	_state->handleInput(*this);
}

void PacmanWS::setImageRect(Texture* t, int rows, int cols, int row, int col)
{
	_img = t;
	int w = _img->width() / rows;
	int h = _img->height() / cols;
	_src = { col * w, row * h, w, h };
}

void PacmanWS::render() {
	SDL_Rect rect = build_sdlrect(_pos, _width, _height);

	_img->render(_src, rect, _rot);

}