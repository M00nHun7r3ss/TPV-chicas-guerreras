// This file is part of the course TPV2@UCM - Samir Genaim

/*
 CORRECCIONES PRÁCTICA 1:
	· Inicializar variables en orden (int a, int b, int c - a(1), b(2), c(3))
	· Siempre inicializar las variables
	· Borrar lo creado en la constructora (p.ejemplo: estados, sistemas...)
	· No llamar clearRenderer() dentro de los estados (??? RUNNING STATE
	· entity_t es un puntero, no hacer entity_t*
	· En vez de definir cosas en métodos, hacerlo en el .h
	· En ImageWithFrames::render() solo renderizamos los frames. En ImageWithFrames::update() solo calculamos el frame a renderizar.
 */

#pragma once

#include "../utils/Singleton.h"

#include <vector>

#include "../ecs/ecs.h"

#include "GameState.h"

namespace ecs
{
	class Manager;
}

class Game : public Singleton<Game> {
	friend Singleton;
public:

	enum State { RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER };

	virtual ~Game();
	bool init();
	void initGame();
	void start();

	inline ecs::Manager* getManager() { return _mngr; }

	inline void setState(State s) {

		_state->leave();
		switch (s) {
		case RUNNING:
			_state = _running_state;
			break;
		case PAUSED:
			_state = _paused_state;
			break;
		case NEWGAME:
			_state = _newgame_state;
			break;
		case NEWROUND:
			_state = _newround_state;
			break;
		case GAMEOVER:
			_state = _gameover_state;
			break;
		default:
			break;
		}
		_state->enter();
	}

	//Getters Systems
	ecs::System* pacmanSys() { return _pacmanSys; }
	ecs::System* ghostSys() { return _ghostSys; }
	ecs::System* renderSys() { return _renderSys; }
	ecs::System* collisionSys() { return _collisionSys; }

private:
	//Privado porque es singleton
	Game();

	ecs::Manager* _mngr;

	//Systems
	ecs::System* _pacmanSys;
	ecs::System* _ghostSys;
	ecs::System* _renderSys;
	ecs::System* _collisionSys;

	//States
	GameState* _state;
	GameState* _running_state;
	GameState* _paused_state;
	GameState* _newgame_state;
	GameState* _newround_state;
	GameState* _gameover_state;
};


