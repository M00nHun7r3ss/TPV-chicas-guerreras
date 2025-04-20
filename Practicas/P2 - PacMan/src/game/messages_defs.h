// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_NEW_GAME, _m_ROUND_START, _m_ROUND_OVER, _m_GAME_OVER, //Estados de juego
	_m_PACMAN_FOOD_COLLISION, //Colisiones
	_m_IMMUNITY_START, _m_IMMUNITY_END, //Inmunidad
	_m_GHOST_COLLISION_IMMUNITY, _m_GHOST_COLLISION_NO_IMMUNITY // Colisiones con ghosts segun immunity
};


struct Message {
	msgId_type id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {
		//	_m_PACMAN_FOOD_COLLISION
		struct {
			ecs::entity_t f;
		} pacman_food_collision_data;

		//	_m_PACMAN_GHOST_COLLISION
		struct {
			ecs::entity_t g;
		} pacman_ghost_collision_data;
	};

	
};
		
