//// This file is part of the course TPV2@UCM - Samir Genaim
//
//#include "PacMan.h"
//
//#include "../sdlutils/InputHandler.h"
//#include "../sdlutils/macros.h"
//#include "../sdlutils/SDLUtils.h"
//#include "../sdlutils/Texture.h"
//
//PacMan::PacMan() :
//		/*_img(nullptr),*/ //
//		/*_walking(false), //
//		_spinning(false), //
//		_still(true), //*/
//		_deg(0.0) //
//		/*_src() *///
//{
//	_width = 50;
//	_height = 50;
//	float x = (sdlutils().width() - _width) / 2;
//	float y = (sdlutils().height() - _height) / 2;
//	_pos.set(x, y);
//	_rot = 90.0f;
//	//setImageRect(&sdlutils().images().at("sprites"), 8, 8, 0, 1);
//	//Estado inicial
//	_state = STILL;
//}
//
//PacMan::~PacMan() {
//}
//
//void PacMan::update() {
//
//	/*
//	if (_walking) {
//		auto p = _pos;
//		_pos = _pos + _vel;
//
//		if (_pos.getY() < 0 || _pos.getY() + _height > sdlutils().height()
//				|| _pos.getX() < 0
//				|| _pos.getX() + _width > sdlutils().width()) {
//			std::cout << "ff" << std::endl;
//			_pos.set(p);
//			_vel.set(0.0f, 0.0f);
//			_walking = false;
//			_still = true;
//			setImageRect(&sdlutils().images().at("sprites"), 8, 8, 0, 1);
//		}
//	}
//
//	if (_spinning) {
//		_rot += _deg;
//	}
//	auto p = _pos;
//	*/
//	switch (_state) {
//	/*case STILL:
//		break;
//	case WALKING:
//
//		_pos = _pos + _vel;
//
//		if (_pos.getY() < 0 || _pos.getY() + _height > sdlutils().height()
//			|| _pos.getX() < 0
//			|| _pos.getX() + _width > sdlutils().width()) {
//			std::cout << "ff" << std::endl;
//			_pos.set(p);
//			_vel.set(0.0f, 0.0f);
//			setImageRect(&sdlutils().images().at("sprites"), 8, 8, 0, 1);
//		}
//		break;
//		*/
//	/*case SPINNING:
//		_rot += _deg;
//		break;
//	}*/
//
//}
//
////void PacMan::render() {
////	SDL_Rect rect = build_sdlrect(_pos, _width, _height);
////
////	_img->render(_src, rect, _rot);
////}
//
////void PacMan::handleInput() {
//	/*auto &ihdlr = ih();*/
//	//switch (_state) {
//	/*case STILL:
//		if (ihdlr.isKeyDown(SDL_SCANCODE_UP)) 
//		{
//			_state = WALKING;
//			_vel = Vector2D(0, -2.0f).rotate(_rot);
//			setImageRect(&sdlutils().images().at("sprites"), 8, 8, 1, 1);
//		}
//		else if (ihdlr.isKeyDown(SDL_SCANCODE_LEFT)
//			|| ihdlr.isKeyDown(SDL_SCANCODE_RIGHT)) 
//		{
//			_state = SPINNING;
//			setImageRect(&sdlutils().images().at("sprites"), 8, 8, 2, 1);
//		}
//
//		break;*/
//	/*case SPINNING:
//		if (ihdlr.isKeyDown(SDL_SCANCODE_LEFT)) {
//			_deg = -5.0f;
//		}
//		else if (ihdlr.isKeyDown(SDL_SCANCODE_RIGHT)) {
//			_deg = 5.0f;
//		}
//		else if (ihdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
//			_state = STILL;
//			setImageRect(&sdlutils().images().at("sprites"), 8, 8, 0, 1);
//		}
//		break;*/
//	/*case WALKING:
//		if (ihdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
//			_state = STILL;
//			setImageRect(&sdlutils().images().at("sprites"), 8, 8, 0, 1);
//		}
//		break;*/
//	}
//
//	/*
//	if (_still) {
//		if (ihdlr.isKeyDown(SDL_SCANCODE_UP)) {
//			_walking = true;
//			_still = false;
//			_vel = Vector2D(0, -2.0f).rotate(_rot);
//			setImageRect(&sdlutils().images().at("sprites"), 8, 8, 1, 1);
//		} else if (ihdlr.isKeyDown(SDL_SCANCODE_LEFT)
//				|| ihdlr.isKeyDown(SDL_SCANCODE_RIGHT)) {
//			_spinning = true;
//			_still = false;
//			setImageRect(&sdlutils().images().at("sprites"), 8, 8, 2, 1);
//		}
//	}
//
//	if (_spinning) {
//		if (ihdlr.isKeyDown(SDL_SCANCODE_LEFT)) {
//			_deg = -5.0f;
//		} else if (ihdlr.isKeyDown(SDL_SCANCODE_RIGHT)) {
//			_deg = 5.0f;
//		} else if (ihdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
//			_spinning = false;
//			_still = true;
//			setImageRect(&sdlutils().images().at("sprites"), 8, 8, 0, 1);
//		}
//	}
//
//	if (_walking) {
//		if (ihdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
//			_walking = false;
//			_still = true;
//			setImageRect(&sdlutils().images().at("sprites"), 8, 8, 0, 1);
//		}
//	}
//	*/
//
////}
//
////void PacMan::setImageRect(Texture *t, int rows, int cols, int row, int col) {
////	_img = t;
////	int w = _img->width() / rows;
////	int h = _img->height() / cols;
////	_src = { col * w, row * h, w, h };
////}
