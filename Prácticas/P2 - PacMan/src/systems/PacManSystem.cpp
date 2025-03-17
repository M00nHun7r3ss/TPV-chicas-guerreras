// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PacManSystem::PacManSystem() :
		_pmTR(nullptr) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	// create the PacMan entity
	ecs::entity_t pacman = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::PACMAN, pacman);

	// add components.
	_mngr->addComponent<Image>(pacman, &sdlutils().images().at("pacman"));
	_pmTR = _mngr->addComponent<Transform>(pacman);

	// pacman's initial position.
	float s = 50.0f;
	float x = (sdlutils().width() - s) / 2.0f;
	float y = (sdlutils().height() - s) / 2.0f;

	// initial parameters
	_pmTR->init(Vector2D(x, y), // pos.
				Vector2D(),		// vel (0.0f,0.0f).
				s,			    // width.
				s,				// height.
				0.0f			// rotation.
	);
}

void PacManSystem::update() {

	InputHandler &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			// sumamos 90.0f grados a la rotación 
			_pmTR->_rot = _pmTR->_rot + 90.0f;

			// y rotamos el vector de velocidad en 90.0f.
			_pmTR->_vel = _pmTR->_vel.rotate(90.0f);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			// restamos 90.0f grados de la rotación 
			_pmTR->_rot = _pmTR->_rot - 90.0f;

			// y rotamos el vector de velocidad en -90.0f grados.
			_pmTR->_vel = _pmTR->_vel.rotate(-90.0f);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed

			// add 1.0f to the speed (respecting the limit 3.0f). Recall
			// that speed is the length of the velocity vector
			float speed = std::min(3.0f, _pmTR->_vel.magnitude() + 1.0f);

			// change the length of velocity vecto to 'speed'. We need
			// '.rotate(rot)' for the case in which the current speed is
			// 0, so we rotate it to the same direction where the PacMan
			// is looking
			//
			_pmTR->_vel = Vector2D(0, -speed).rotate(_pmTR->_rot);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { // decrease speed
			// subtract 1.0f to the speed (respecting the limit 0.0f). Recall
			// that speed is the length of the velocity vector
			float speed = std::max(0.0f, _pmTR->_vel.magnitude() - 1.0f);

			// change the length of velocity vector to 'speed'. We need
			// '.rotate(rot)' for the case in which the current speed is
			// 0, so we rotate it to the same direction where the PacMan
			// is looking
			//
			_pmTR->_vel = Vector2D(0, -speed).rotate(_pmTR->_rot);
		}

	}

	// move the pacman
	_pmTR->_pos = _pmTR->_pos + _pmTR->_vel;

	// check left/right borders
	if (_pmTR->_pos.getX() < 0) {
		_pmTR->_pos.setX(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	} else if (_pmTR->_pos.getX() + _pmTR->_width > sdlutils().width()) {
		_pmTR->_pos.setX(sdlutils().width() - _pmTR->_width);
		_pmTR->_vel.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (_pmTR->_pos.getY() < 0) {
		_pmTR->_pos.setY(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	} else if (_pmTR->_pos.getY() + _pmTR->_height > sdlutils().height()) {
		_pmTR->_pos.setY(sdlutils().height() - _pmTR->_height);
		_pmTR->_vel.set(0.0f, 0.0f);
	}

}
