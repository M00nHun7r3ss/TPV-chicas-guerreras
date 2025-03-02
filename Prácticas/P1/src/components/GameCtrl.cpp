// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrl.h"

#include <algorithm>
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Image.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/AsteroidMotion.h"
#include "../components/Follow.h"

GameCtrl::GameCtrl() :
		_currNumOfAsteroids(0), 
		_score(0), 
		_asteroidsLimit(30)
{
}

GameCtrl::GameCtrl(Transform* playerTf) :
		_currNumOfAsteroids(0),
		_score(0),
		_asteroidsLimit(30),
		_playerTf(playerTf)
{
}

GameCtrl::~GameCtrl() {
}

void GameCtrl::initComponent() {
}

void GameCtrl::update() {
	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {
		if (ihldr.isKeyDown(SDL_SCANCODE_SPACE)) { // create star
			createAsteroid(std::min(5u, _asteroidsLimit - _currNumOfAsteroids));
		}
	}

	
}

void GameCtrl::render() {

	// draw the score
	//
	Texture scoreTex(sdlutils().renderer(), std::to_string(_score),
			sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x444444ff));

	SDL_Rect dest = build_sdlrect( //
			(sdlutils().width() - scoreTex.width()) / 2.0f, //
			10.0f, //
			scoreTex.width(), //
			scoreTex.height());

	scoreTex.render(dest);

	// draw add stars message
	//sdlutils().msgs().at("addstars").render(10, 10);
}

void GameCtrl::createAsteroid(unsigned int n) {

	ecs::Manager *mngr = _ent->getMngr();

	for (unsigned int i = 0u; i < n; i++) {
		// Always use the random number generator provided by SDLUtils
		RandomNumberGenerator &rand = sdlutils().rand();

		// add and entity to the manager
		ecs::entity_t e = mngr->addEntity(ecs::grp::ASTEROIDS);

		// add a Transform component, and initialise it with random size and position
		Transform* tr = mngr->addComponent < Transform > (e);

		// --- POS ALEATORIA ---
		int size = 50;
		//Lado por el que sale
		//0 - arriba, 1 - abajo, 2 - izqd, 3 - dcha
		int lado = rand.nextInt(0, 4); //Hasta max + 1, como el Rnd.Next de C#
		int x, y;
		switch (lado) //Esto es asi porque el origen del sprite es arriba izquierda 
		{
		case 0: //Arriba
			x = rand.nextInt(0, sdlutils().width() - size);
			y = rand.nextInt(0, size); 
			break;
		case 1: //Abajo
			x = rand.nextInt(0, sdlutils().width() - size); 
			y = rand.nextInt(sdlutils().height() - 2*size, sdlutils().height() - size);
			break;
		case 2: //Izquierda
			x = rand.nextInt(0, size);
			y = rand.nextInt(0, sdlutils().height() - size);
			break;
		case 3: //Derecha
			x = rand.nextInt(sdlutils().width() - 2 * size, sdlutils().width() - size);
			y = rand.nextInt(0, sdlutils().height() - size);
			break;
		default:
			break;
		}

		// --- VELOCIDAD ALEATORIA ---
		//Centro ventana para que los asteroides vayan hacia el centro
		Vector2D _centroVent = { (float)(sdlutils().width() / 2) , (float)(sdlutils().height() / 2) };
		int rx = rand.nextInt(-100, 101);
		int ry = rand.nextInt(-100, 101);
		Vector2D centro = { _centroVent.getX() + rx, _centroVent.getY() + ry};

		float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
		Vector2D v = (centro - Vector2D(x, y)).normalize() * speed;

		// inicializa el asteroide en ese transform
		tr->init(Vector2D(x, y), v, size, size, 0.0f);

		// Los demas componentes
		mngr->addComponent<Image>(e, &sdlutils().images().at("star")); // add an Image Componet (cambiar luego).
		mngr->addComponent<ShowAtOppositeSide>(e); // add ShowAtOppositeSide Component.

		// add a StarMotion component to resize/rotate the star
		mngr->addComponent<AsteroidMotion>(e);
		mngr->addComponent<Follow>(e, _playerTf);

		_currNumOfAsteroids++;
	}
}
