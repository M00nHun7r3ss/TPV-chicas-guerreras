// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>

#include "../utils/Vector2D.h"

class GameObject {
public:
	GameObject() :
			_pos(), _vel(), _width(), _height(), _rot(), _alive(true) {
	}
	virtual ~GameObject() {
	}

	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	inline float getHeight() const {
		return _height;
	}

	inline void setHeight(float height) {
		_height = height;
	}

	inline Vector2D& getPos() {
		return _pos;
	}

	inline Vector2D& getVel() {
		return _vel;
	}

	inline float getWidth() const {
		return _width;
	}

	inline void setWidth(float width) {
		_width = width;
	}

	inline bool isAlive() {
		return _alive;
	}

	inline void setAlive(bool b) {
		_alive = b;
	}

	float getRot() const {
		return _rot;
	}

	void setRot(float rot) {
		_rot = rot;
	}

protected:

	Vector2D _pos;
	Vector2D _vel;
	float _width;
	float _height;
	float _rot;
	bool _alive;
};

