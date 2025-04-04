// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// Components list - must have at least one element
//
struct Transform;
struct Image;
struct StarMotion;
struct Points;
struct Health;
struct ImageWithFrames;

#define _CMPS_LIST_ \
	Transform, \
	Image, \
	StarMotion, \
	Points, \
	Health, \
	ImageWithFrames

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	GHOSTS, \
	HEALTH, \
	FRUITS

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    PACMAN

// Systems list - must have at least one element
//
class GhostSystem;
class RenderSystem;
class PacManSystem;
class GameCtrlSystem;
class CollisionsSystem;
class FoodSystem;

#define _SYS_LIST_ \
    GhostSystem, \
	RenderSystem, \
	PacManSystem, \
	GameCtrlSystem, \
	CollisionsSystem, \
	FoodSystem

