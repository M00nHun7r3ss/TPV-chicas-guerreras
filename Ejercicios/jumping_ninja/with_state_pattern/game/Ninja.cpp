// This file is part of the course TPV2@UCM - Samir Genaim

#include "../game/Ninja.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

Ninja::Ninja() :
		_img(&sdlutils().images().at("ninja_standing")),
	    _speed(), 
	    _charge() 
{
	_width = 100;
	_height = 100;
	float x = (sdlutils().width() - _width) / 2;
	float y = sdlutils().height() - _height;
	_pos.set(x, y);
	_state = STANDING;
}

Ninja::~Ninja() {
}

void Ninja::update() {
	switch (_state) {
	case STANDING:
		break;
	case WALKING:
		_pos.setX(_pos.getX() + _speed);
		break;
	case JUMPING:
		_pos.setY(_pos.getY() + _speed);
		if (_speed < 0) {
			_speed *= 0.9;
			if (_speed > -1.0f) {
				_speed = 10.0f;
			}
		} else {
			_speed *= 1.1f;
			if (_pos.getY() + _height > sdlutils().height()) {
				_pos.setY(sdlutils().height() - _height);
				_speed = 0.0f;
				_img = &sdlutils().images().at("ninja_standing");
				_state = STANDING;
			}
		}
		break;
	case ATTACKING:
		_pos.setY(_pos.getY() + _speed);
		_pos.setX(_pos.getX() + 5.0f);
		if (_speed < 0) {
			_speed *= 0.9;
			if (_speed > -1.0f) {
				_speed = 10.0f;
			}
		} else {
			_speed *= 1.1f;
			if (_pos.getY() + _height > sdlutils().height()) {
				_pos.setY(sdlutils().height() - _height);
				_speed = 0.0f;
				_img = &sdlutils().images().at("ninja_standing");
				_state = STANDING;
				_charge = 0.0f;
			}
		}

		break;
	default:
		break;
	}
}

void Ninja::render() {
	SDL_Rect rect = build_sdlrect(_pos, _width, _height);

	_img->render(rect);
}

void Ninja::handleInput() {
	auto &ihdlr = ih();
	switch (_state) {
	case STANDING:
		if (ihdlr.isKeyDown(SDLK_RIGHT) || ihdlr.isKeyDown(SDLK_LEFT)) {
			_img = &sdlutils().images().at("ninja_walking");
			_state = WALKING;
		} else if (ihdlr.isKeyDown(SDLK_UP)) {
			_img = &sdlutils().images().at("ninja_jumping");
			_state = JUMPING;
			_speed = -10.0f;
		} else if (ihdlr.isKeyDown(SDLK_DOWN)) {
			_img = &sdlutils().images().at("ninja_ducking");
			_state = DUCKING;
			_charge = 0.0f;
		}
		break;
	case WALKING:
		if (ihdlr.isKeyDown(SDLK_RIGHT)) {
			_speed = 5.0f;
		} else if (ihdlr.isKeyDown(SDLK_LEFT)) {
			_speed = -5.0f;
		} else {
			_img = &sdlutils().images().at("ninja_standing");
			_state = STANDING;
			_speed = 0.0f;
		}
		break;
	case JUMPING:
		break;
	case DUCKING:
		if (ihdlr.isKeyDown(SDLK_DOWN)) {
			_charge += 0.01f;
			if (_charge > 1.0f) {
				_speed = -10.0f;
				_charge = 0.0f;
				_state = ATTACKING;
				_img = &sdlutils().images().at("ninja_attacking");

			}
		} else {
			_img = &sdlutils().images().at("ninja_standing");
			_charge = 0.0f;
			_state = STANDING;
		}
		break;
	case ATTACKING:
		break;
	}
}
