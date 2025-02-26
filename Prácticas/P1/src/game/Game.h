// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

namespace ecs {
class Manager;
}

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
	void refresh();
private:
	void checkCollisions();
	ecs::Manager *_mngr;
};

