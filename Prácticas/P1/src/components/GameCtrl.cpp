// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrl.h"

#include <algorithm>
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Image.h"
#include "StarMotion.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "../components/ShowAtOppositeSide.h"

GameCtrl::GameCtrl() :
		_currNumOfAsteroids(0), //
		_score(0), //
		_asteroidsLimit(30) {
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

	auto *mngr = _ent->getMngr();

	for (auto i = 0u; i < n; i++) {
		// Always use the random number generator provided by SDLUtils
		auto &rand = sdlutils().rand();

		// add and entity to the manager
		auto e = mngr->addEntity(ecs::grp::ASTEROIDS);

		// add a Transform component, and initialise it with random size and position
		auto tr = mngr->addComponent < Transform > (e);
		auto s = rand.nextInt(50, 100);
		auto x = rand.nextInt(0, sdlutils().width() - s);
		auto y = rand.nextInt(0, sdlutils().height() - s);
		tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

		mngr->addComponent<Image>(e, &sdlutils().images().at("star")); // add an Image Componet (cambiar luego).
		mngr->addComponent<ShowAtOppositeSide>(e); // add ShowAtOppositeSide Component.

		// add a StarMotion component to resize/rotate the star
		mngr->addComponent<StarMotion>(e);

		_currNumOfAsteroids++;
	}
}
