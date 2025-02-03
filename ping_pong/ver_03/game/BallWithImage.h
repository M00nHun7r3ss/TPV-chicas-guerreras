// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "Ball.h"

class Texture;

class BallWithImage: public Ball {
public:
	BallWithImage(Texture *img);
	virtual ~BallWithImage();
	void render() override;

private:
	Texture *_img;
};

