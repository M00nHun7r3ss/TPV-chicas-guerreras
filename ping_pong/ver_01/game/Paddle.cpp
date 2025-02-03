// This file is part of the course TPV2@UCM - Samir Genaim

#include "Paddle.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

Paddle::Paddle() :
		Paddle(build_sdlcolor(0xffffffff)) //
{
}

Paddle::Paddle(SDL_Color color) :
		_color(color), //
		_up(SDL_SCANCODE_UP), //
		_down(SDL_SCANCODE_DOWN), //
		_stop(SDL_SCANCODE_LEFT), //
		_speed(10.0f) //
{
}

Paddle::~Paddle() {

}

void Paddle::handleInput(const SDL_Event &e) {

	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.scancode == _up) {
			_vel.setY(-_speed);
		} else if (e.key.keysym.scancode == _down) {
			_vel.setY(_speed);
		} else if (e.key.keysym.scancode == _stop) {
			_vel.setY(0.0f);
		}
	}
}

void Paddle::update() {
	_pos = _pos + _vel;

	if (_pos.getY() < 0) {
		_pos.setY(0);
		_vel.setY(0);
	} else if (_pos.getY() + _height > sdlutils().height()) {
		_pos.setY(sdlutils().height() - _height);
		_vel.setY(0);
	}

}

void Paddle::render() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(_color));

	SDL_Rect rect = build_sdlrect(_pos.getX(), _pos.getY(), _width, _height);

	SDL_RenderFillRect(sdlutils().renderer(), &rect);
}
