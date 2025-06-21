// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_rect.h>
#include "../game/GameObject.h"

class Texture;
class PacMan: public GameObject {
public:
	PacMan();
	virtual ~PacMan();
	void update() override;
	void render() override;
	void handleInput() override;
	void setImageRect(Texture *t, int rows, int cols, int row, int col);
private:
	/*Texture *_img;*/

	//Lo de antes
	/*
	bool _walking;
	bool _spinning;
	bool _still;*/

	//En vez de mirar con booleans en que estado esta, tenemos un enum
	enum State {
		WALKING, SPINNING, STILL
	};
	State _state;

	float _deg;

	/*SDL_Rect _src;*/
};

