// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../utils/Singleton.h"

namespace ecs {
class Manager;
}

class Game : public Singleton<Game> {
public:
	virtual ~Game();
	bool init();
	void initGame();
	void start();
	void refresh();
	inline ecs::Manager* getManager() { return _mngr; }
private:
	Game();
	void checkCollisions();
	ecs::Manager *_mngr;
};

