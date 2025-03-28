// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawMsgs();
	drawStars();
	drawPacMan();
}

void RenderSystem::drawStars() {
	// draw ghosts
	for (ecs::entity_t e : _mngr->getEntities(ecs::grp::GHOSTS)) {

		Transform* tr = _mngr->getComponent<Transform>(e);
		Texture* tex = _mngr->getComponent<Image>(e)->_tex;
		draw(tr, tex);
	}
}

void RenderSystem::drawPacMan() {
	ecs::entity_t e = _mngr->getHandler(ecs::hdlr::PACMAN);
	Transform* tr = _mngr->getComponent<Transform>(e);
	Texture* tex = _mngr->getComponent<Image>(e)->_tex;
	draw(tr, tex);

}


void RenderSystem::drawMsgs() {
	// draw the score
	//
	//auto score = _mngr->getSystem<GameCtrlSystem>()->getScore();

	//Texture scoreTex(sdlutils().renderer(), std::to_string(score),
	//		sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x444444ff));

	//SDL_Rect dest = build_sdlrect( //
	//		(sdlutils().width() - scoreTex.width()) / 2.0f, //
	//		10.0f, //
	//		scoreTex.width(), //
	//		scoreTex.height());

	//scoreTex.render(dest);

	//// draw add stars message
	//sdlutils().msgs().at("addstars").render(10, 10);

}

void RenderSystem::drawHealth()
{
	// draw hearts
	for (ecs::entity_t e : _mngr->getEntities(ecs::grp::HEALTH)) {

		Transform* tr = _mngr->getComponent<Transform>(e);
		Texture* tex = _mngr->getComponent<Image>(e)->_tex;
		draw(tr, tex);
		// vamos modificando la x y renderizando para que vayan en fila.
		tr->_pos.setX(tr->_pos.getX()+45);
	}

	//// pos arriba izquierda.
	//SDL_Rect dest = { 5, 10, 40, 40 };

	//// vamos modificando la x y renderizando para que vayan en fila.
	//for (int i = 0; i < _currentHealth; i++) {

	//	dest.x = dest.x + 45;
	//}
}

void RenderSystem::draw(Transform *tr, Texture *tex) {
	SDL_Rect dest = build_sdlrect(tr->_pos, tr->_width, tr->_height);

	assert(tex != nullptr);
	tex->render(dest, tr->_rot);
}
