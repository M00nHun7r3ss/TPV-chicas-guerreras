// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include <vector>

#include "../utils/Singleton.h"

class Networking;

class LittleWolf;

class Game
	: public Singleton<Game>
{
	friend Singleton<Game>;
	Game();
public:
	virtual ~Game();

	bool init(const char* map, char* host, Uint16 port);

	void initGame();

	void start();

	LittleWolf& get_littlewolf()
	{
		return *_little_wolf;
	}

	Networking& get_networking() {
		return *net_;
	}

private:

	//void check_collisions();

	Networking *net_;

	LittleWolf* _little_wolf;
};

