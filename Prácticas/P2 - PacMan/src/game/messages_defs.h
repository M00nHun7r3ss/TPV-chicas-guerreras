// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_NEW_GAME, _m_ROUND_START, _m_ROUND_OVER, _m_GAME_OVER, //Estados de juego
	_m_PACMAN_FOOD_COLLISION, _m_PACMAN_GHOST_COLLISION, //Colisiones
	_m_IMMUNITY_START, _m_IMMUNITY_END //Inmunidad
};


struct Message {
	msgId_type id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {

		// _m_STAR_EATEN
		struct {
			ecs::entity_t e;
		} ghost_eaten_data;

		// _m_CREATE_STARS
		struct {
			unsigned int n;
		} create_ghost_data;

	};
};
