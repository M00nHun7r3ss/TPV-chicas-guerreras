#include "FighterCtrl.h"

#include "../sdlutils/InputHandler.h"
#include "Container.h"

FighterCtrl::FighterCtrl() :
	_left(SDL_SCANCODE_LEFT),
	_right(SDL_SCANCODE_RIGHT),
	_rot(5.0f)
{
}

FighterCtrl::~FighterCtrl()
{
}

void FighterCtrl::handleInput(Container* o)
{
	auto& ihdlr = ih();

	//  ihdlr.keyDownEvent() && ihdlr.isKeyDown(...). Movimiento más discreto. 
	// Va guardando el input en el buffer y lo va usando poco a poco
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(_left)) {
		o->setRotation(o->getRotation() - _rot);
	}
	else if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(_right)) {
		o->setRotation(o->getRotation() + _rot);
	}

	// ihdlr.isKeyDown(...). Da más fluidez
	if (ihdlr.isKeyDown(_left)) {
		o->setRotation(o->getRotation() - _rot);
	}
	else if (ihdlr.isKeyDown(_right)) {
		o->setRotation(o->getRotation() + _rot);
	}
}
