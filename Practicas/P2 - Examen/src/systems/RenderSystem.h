// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class Texture;
struct Transform;

class RenderSystem: public ecs::System {
public:

	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;
private:
	void drawGhosts();
	void drawPacMan();
	void drawHealth();
	void drawFruitGrid();
	void drawImageWithFrames(Transform* t, ImageWithFrames* img);
	void draw(Transform *tr, Texture *tex);
};

