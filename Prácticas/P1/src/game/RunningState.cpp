#include "RunningState.h"

#include "../ecs/Manager.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

#include "../utils/Collisions.h"

#include <vector>

#include "../components/Transform.h"
#include "../components/Gun.h"

void RunningState::update()
{
	bool exit = false;

	// Si hay 0 asteroides cambia al estado GameOverState y sale del metodo.
	if (_aUtils->getAsteroidNumber() == 0 && !exit) {
		_g->setState(Game::GAMEOVER);
		exit = true;
	}

	// Si el usuario pulsa la tecla P cambia al estado PauseState y sale del metodo.
	InputHandler& ihldr = ih();
	if (ihldr.keyDownEvent() && ihldr.isKeyDown(SDLK_p) && !exit) {
		_g->setState(Game::PAUSED);
		exit = true;
	}

	// Actualizar entidad de caza y asteroides
	std::vector<ecs::entity_t> asteroidsEnt = _g->getManager()->getEntities(ecs::grp::ASTEROIDS);
	for (entity_t asteroid : asteroidsEnt)
	{
		_g->getManager()->update(asteroid);
	}

	entity_t fighterEnt = _g->getManager()->getHandler(ecs::hdlr::FIGHTER);
	_g->getManager()->update(fighterEnt);

	//Comprueba colisiones
	checkCollisions();

	// Renderiza las entidades de caza y asteroides
	for (entity_t asteroid : asteroidsEnt)
	{
		_g->getManager()->render(asteroid);
	}

	_g->getManager()->render(fighterEnt);

	//Quita entidades muertas
	_g->getManager()->refresh();

	// Anade asteroide cada 5 segundos
	// Inicialmente empieza en 5 segundos.
	Uint32 _timeBetweenEachSpawn = 5000;

	auto& vt = sdlutils().virtualTimer();

	if (vt.currTime() > _timeBetweenEachSpawn + _lastAsteroidAdded) {
		_aUtils->create_asteroids(1);
	}
}

void RunningState::checkCollisions()
{
	// the fighters Transform
	auto fighter = _g->getManager()->getHandler(ecs::hdlr::FIGHTER);
	auto playerTF = _g->getManager()->getComponent<Transform>(fighter);
	auto playerGun = _g->getManager()->getComponent<Gun>(fighter);

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list asteroids is not
	// modified.

	//get asteroids vector
	auto& asteroids = _g->getManager()->getEntities(ecs::grp::ASTEROIDS);
	//size of vector
	auto n = _aUtils->getAsteroidNumber();
	//looks each asteroid
	for (auto i = 0u; i < n; i++) {
		auto e = asteroids[i];
		if (_g->getManager()->isAlive(e)) { // if the asteroid is active (it might have died in this frame)

			// the Asteroid's Transform
			auto aTR = _g->getManager()->getComponent<Transform>(e);

			// check if Fighter collides with the Asteroids 
			if (Collisions::collidesWithRotation(playerTF->getPos(), playerTF->getWidth(),playerTF->getHeight(), playerTF->getRot(), 
				aTR->getPos(), aTR->getWidth(), aTR->getHeight(), aTR->getRot())) 
			{
				//Quita una vida, si le quedan, reinicia ronda
				if (_fUtils->update_lives(-1) > 0) {
					// !!! cambia a NewRoundState
					Game::Instance()->setState(Game::NEWROUND);
				}
				else {
					// !!! cambia a GameOverState
					Game::Instance()->setState(Game::GAMEOVER);
				}
			}
			//SI HAY CHOQUE, NO TIENE QUE SEGUIR COMPROBANDO??

			//Recorremos las balas
			for (Gun::Bullet& b : *playerGun)
			{
				//Si estan usadas
				if (b.used)
				{
					//Mira la colision
					if (Collisions::collidesWithRotation(b.pos, b.getBulletWidth(), b.getBulletHeight(), b.rot,
						aTR->getPos(), aTR->getWidth(), aTR->getHeight(), aTR->getRot()))
					{
						//Split asteroid
						_aUtils->split_asteroid(e);

						//Bullet not used
						b.used = false;
					}
				}
			}
	
		}
	}
}
