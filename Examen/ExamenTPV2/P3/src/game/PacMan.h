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
	Texture *_img;
	bool _walking;
	bool _spinning;
	bool _still;

	float _deg;

	SDL_Rect _src;
};

