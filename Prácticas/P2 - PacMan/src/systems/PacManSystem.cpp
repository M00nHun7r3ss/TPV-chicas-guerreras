// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Health.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PacManSystem::PacManSystem() :
		_pmTR(nullptr), _pmHealth(nullptr) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	// create the PacMan entity
	ecs::entity_t pacman = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::PACMAN, pacman);

	_pmTR = _mngr->addComponent<Transform>(pacman);
	_mngr->addComponent<ImageWithFrames>(pacman, &sdlutils().images().at("sprites"), 0, 0, 4);
	_pmHealth = _mngr->addComponent<Health>(pacman, &sdlutils().images().at("heart"));

	resetPacman();
}

void PacManSystem::update() {

	pacmanInput();

	// move the pacman
	_pmTR->_pos = _pmTR->_pos + _pmTR->_vel;

	stopOnBorders();
}

void PacManSystem::resetPacman()
{
	// resets pacman's initial position.
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

void PacManSystem::recieve(const Message& m)
{
	VirtualTimer& vt = sdlutils().virtualTimer();
	switch (m.id)
	{
	case _m_NEW_GAME:
		// al empezar juego resetea vidas.
		maxHealth();
		//Reseteamos el tiempo
		vt.resetTime();
		break;

	case _m_ROUND_START:
		// al empezar ronda resetea posicion.
		resetPacman();
		break;

	default:
		break;
	}
}

void PacManSystem::stopOnBorders()
{
	// check left/right borders
	if (_pmTR->_pos.getX() < 0) {
		_pmTR->_pos.setX(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	}
	else if (_pmTR->_pos.getX() + _pmTR->_width > sdlutils().width()) {
		_pmTR->_pos.setX(sdlutils().width() - _pmTR->_width);
		_pmTR->_vel.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (_pmTR->_pos.getY() < 0) {
		_pmTR->_pos.setY(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	}
	else if (_pmTR->_pos.getY() + _pmTR->_height > sdlutils().height()) {
		_pmTR->_pos.setY(sdlutils().height() - _pmTR->_height);
		_pmTR->_vel.set(0.0f, 0.0f);
	}
}

void PacManSystem::pacmanInput()
{
	InputHandler& ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			// sumamos 90.0f grados a la rotaci�n 
			_pmTR->_rot = _pmTR->_rot + 90.0f;

			// y rotamos el vector de velocidad en 90.0f.
			_pmTR->_vel = _pmTR->_vel.rotate(90.0f);

		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			// restamos 90.0f grados de la rotaci�n 
			_pmTR->_rot = _pmTR->_rot - 90.0f;

			// y rotamos el vector de velocidad en -90.0f grados.
			_pmTR->_vel = _pmTR->_vel.rotate(-90.0f);

		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) {

			//ponemos la velocidad a 0.0f, -3.0f, con su rotacion actual
			_pmTR->_vel = Vector2D(0.0f, -3.0f).rotate(_pmTR->_rot);

		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) {

			//ponemos la velocidad a 0.0f, 0.0f, con su rotacion actual
			_pmTR->_vel = Vector2D(0.0f, 0.0f).rotate(_pmTR->_rot);
		}
	}
}

void PacManSystem::maxHealth()
{
	_pmHealth->_currentHealth = _pmHealth->MAX_HEALTH;
}
