// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class GameObject;

class Game {

public:
	Game();
	virtual ~Game();
	void start();
	bool init();
private:
	std::vector<GameObject*> _objs;
};

