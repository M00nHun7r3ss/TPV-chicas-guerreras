// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// Components list - must have at least one element
//
struct Transform;
struct Image;
struct Health;
struct ImageWithFrames;
struct MiraculousComponent;
struct ClonableGhostComponent;

#define _CMPS_LIST_ \
	Transform, \
	Image, \
	Health, \
	ImageWithFrames, \
	MiraculousComponent, \
	ClonableGhostComponent

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	GHOSTS, \
	FRUITS, \
	SHIELDS

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    PACMAN

// Systems list - must have at least one element
//
class GhostSystem;
class RenderSystem;
class PacManSystem;
class CollisionsSystem;
class FoodSystem;
class ImmunitySystem;
class ShieldSystem;

#define _SYS_LIST_ \
    GhostSystem, \
	RenderSystem, \
	PacManSystem, \
	CollisionsSystem, \
	FoodSystem, \
	ImmunitySystem, \
	ShieldSystem

