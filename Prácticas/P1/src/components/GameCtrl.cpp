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



/*void GameCtrl::update() {
	InputHandler &ihldr = ih();

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
}*/
