// This file is part of the course TPV2@UCM - Samir Genaim

#include "../game/Ninja.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

Ninja::Ninja() :
		_img(&sdlutils().images().at("ninja_standing")), //
		_speed() //
{
	_width = 100;
	_height = 100;
	float x = (sdlutils().width() - _width) / 2;
	float y = sdlutils().height() - _height;
	_pos.set(x, y);
}

Ninja::~Ninja() {
}

void Ninja::update() {
	_pos.setX(_pos.getX() + _speed);
}

void Ninja::render() {
	SDL_Rect rect = build_sdlrect(_pos, _width, _height);
	_img->render(rect);
}

void Ninja::handleInput() {
	auto &ihdlr = ih();
	if (ihdlr.isKeyDown(SDLK_RIGHT)) {
		_speed = 5.0f;
	} else if (ihdlr.isKeyDown(SDLK_LEFT)) {
		_speed = -5.0f;
	} else {
		_speed = 0.0f;
	}
}
