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

namespace ecs
{
	class Manager;
}

	class Game : public Singleton<Game> {
		friend Singleton;
	public:
		virtual ~Game();
		bool init();
		void initGame();
		void start();

		inline ecs::Manager* getManager() { return _mngr; }

	private:
		Game();
		ecs::Manager* _mngr;
		ecs::System* _pacmanSys;
		ecs::System* _gameCtrlSys;
		ecs::System* _startsSys;
		ecs::System* _renderSys;
		ecs::System* _collisionSys;
	};


