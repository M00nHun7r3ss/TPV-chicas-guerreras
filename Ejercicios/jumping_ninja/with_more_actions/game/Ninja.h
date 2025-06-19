// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../game/GameObject.h"

class Texture;
class Ninja: public GameObject {
public:
	Ninja();
	virtual ~Ninja();
	void update() override;
	void render() override;
	void handleInput() override;
private:
	Texture *_img;
	enum State {
		STANDING, JUMPING, WALKING, DUCKING, ATTACKING
	};

	State _state;

	float _speed;
	float _charge;
	

};

