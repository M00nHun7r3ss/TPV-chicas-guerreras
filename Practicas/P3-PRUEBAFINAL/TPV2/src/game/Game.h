// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include <vector>

#include "../utils/Singleton.h"

//class Fighter;
//class Bullets;
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
	/*
	Fighter& get_fighters() {
		return *fighters_;
	}

	Bullets& get_bullets() {
		return *bm_;
	}
	*/

	LittleWolf& get_littlewolf()
	{
		return *_little_wolf;
	}

	Networking& get_networking() {
		return *net_;
	}

private:

	//bool init(); // TODO: ver que pasa con los init.
	//void check_collisions();


	//Bullets *bm_;
	//Fighter *fighters_;
	Networking *net_;

	LittleWolf* _little_wolf;
};

