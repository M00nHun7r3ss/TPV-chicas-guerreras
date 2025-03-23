// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// Components list - must have at least one element
//
struct Transform;
struct Image;
struct StarMotion;
struct Points;
//struct Health;

#define _CMPS_LIST_ \
	Transform, \
	Image, \
	StarMotion, \
	Points
	//Health

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	STARS, \
	GHOSTS, \

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    PACMAN

// Systems list - must have at least one element
//
class GhostSystem;
//class RenderSystem;
class PacManSystem;
//class GameCtrlSystem;
//class CollisionsSystem;

#define _SYS_LIST_ \
    GhostSystem, \
	PacManSystem
	//RenderSystem, \
	//GameCtrlSystem, \
	//CollisionsSystem

