// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/Health.h"
#include "../components/ImageWithFrames.h"
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
	drawGhosts();
	drawPacMan();
	drawFruitGrid();
	drawHealth();
}

void RenderSystem::drawGhosts() {
	// draw ghosts
	for (ecs::entity_t e : _mngr->getEntities(ecs::grp::GHOSTS)) {

		Transform* tr = _mngr->getComponent<Transform>(e);
		ImageWithFrames* imgwf = _mngr->getComponent<ImageWithFrames>(e);
		drawImageWithFrames(tr, imgwf);
	}
}

void RenderSystem::drawPacMan() {
	ecs::entity_t e = _mngr->getHandler(ecs::hdlr::PACMAN);
	Transform* tr = _mngr->getComponent<Transform>(e);
	ImageWithFrames* imgwf = _mngr->getComponent<ImageWithFrames>(e);
	drawImageWithFrames(tr, imgwf);

}

void RenderSystem::drawHealth()
{
	ecs::entity_t e = _mngr->getHandler(ecs::hdlr::PACMAN);
	Health* pmHealth = _mngr->getComponent<Health>(e);
	Vector2D pos = { 10.0f, 5.0f };
	
	// draw hearts
	for (int i = 0; i <= pmHealth->_currentHealth; i++) {

		Texture* tex = pmHealth->getTexture();
		// vamos modificando la x y renderizando para que vayan en fila.

		pos.setX(pos.getX() + 35.0f);
		SDL_Rect dest = build_sdlrect(pos, 30.0f, 30.0f);

		assert(tex != nullptr);
		tex->render(dest);
	}
}

void RenderSystem::drawFruitGrid()
{
	// draw fruits
	for (ecs::entity_t e : _mngr->getEntities(ecs::grp::FRUITS)) {
		
		Transform* tr = _mngr->getComponent<Transform>(e);
		ImageWithFrames* imgwf = _mngr->getComponent<ImageWithFrames>(e);
		drawImageWithFrames(tr, imgwf);
	}
}

void RenderSystem::drawImageWithFrames(Transform* t, ImageWithFrames* img)
{
	// Inicialmente empieza en 0.5 segundos.
	Uint32 _timeBetweenEachSpawn = 50; 

	VirtualTimer& vt = sdlutils().virtualTimer();

	//Gestion de frames
	if (vt.currRealTime() > _timeBetweenEachSpawn + img->_lastFrame) {
		//Si hay más de un frame, se anima
		if (img->_nFrames > 1)
		{
			// va haciendo fcol++ y reinicia a 0 al llegar al final
			img->_fCol = (img->_fCol + 1) % img->_nFrames;
		}

		// Reinicia el contador
		img->_lastFrame = vt.currRealTime();
	}

	// --- RECTANGULO SOURCE: gestion de la propia textura (como avanza, como se muestra, como se renderiza)
	SDL_Rect src = build_sdlrect(
		img->_fCol * (img->_tex->width() / img->COLS),	// posX * (anchura de cada fila).
		img->_fRow * (img->_tex->height() / img->ROWS),  // posY * (altura de cada fila).
		img->_tex->width() / img->COLS,				// anchura textura / columnas.
		img->_tex->height() / img->ROWS				// altura textura / filas.
	);

	// --- RECTANGULO DESTINO: rectangulo del asteroide ingame y ya.
	SDL_Rect dest = build_sdlrect(
		t->_pos.getX(),	    // pos x asteroide)
		t->_pos.getY(),		// pos y asteroide
		t->_width,		    // en horizontal hay 6 frames.
		t->_height	    // en vertical hay 5 frames.
	);

	img->_tex->render(src, dest, t->_rot);
}

void RenderSystem::draw(Transform *tr, Texture *tex) {
	SDL_Rect dest = build_sdlrect(tr->_pos, tr->_width, tr->_height);

	assert(tex != nullptr);
	tex->render(dest, tr->_rot);
}
