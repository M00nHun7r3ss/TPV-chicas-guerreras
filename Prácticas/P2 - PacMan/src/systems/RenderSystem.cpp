// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
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
	//drawGhosts();
	drawPacMan();
	//drawHealth();
	drawFruitGrid();
}

void RenderSystem::drawGhosts() {
	// draw ghosts
	for (ecs::entity_t e : _mngr->getEntities(ecs::grp::GHOSTS)) {

		Transform* tr = _mngr->getComponent<Transform>(e);
		//ImageWithFrames* imgwf = _mngr->getComponent<ImageWithFrames>(e);
		//drawImageWithFrames(tr, imgwf);
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

void RenderSystem::drawHealth()
{
	// draw hearts
	for (ecs::entity_t e : _mngr->getEntities(ecs::grp::HEALTH)) {

		Transform* tr = _mngr->getComponent<Transform>(e);
		Texture* tex = _mngr->getComponent<Image>(e)->_tex;
		draw(tr, tex);
		// vamos modificando la x y renderizando para que vayan en fila.
		tr->_pos.setX(tr->_pos.getX()+55);
	}

	//// pos arriba izquierda.
	//SDL_Rect dest = { 5, 10, 40, 40 };

	//// vamos modificando la x y renderizando para que vayan en fila.
	//for (int i = 0; i < _currentHealth; i++) {

	//	dest.x = dest.x + 45;
	//}
}

void RenderSystem::drawFruitGrid()
{
	// draw fruits
	for (ecs::entity_t e : _mngr->getEntities(ecs::grp::FRUITS)) {
		
		Transform* tr = _mngr->getComponent<Transform>(e);
		Texture* tex = _mngr->getComponent<Image>(e)->_tex;
		draw(tr, tex);
	}
}

void RenderSystem::drawImageWithFrames(Transform* t, ImageWithFrames* img)
{
	// Inicialmente empieza en 0.5 segundos.
	Uint32 _timeBetweenEachSpawn = 50;

	VirtualTimer& vt = sdlutils().virtualTimer();

	//Gestion de frames
	if (vt.currTime() > _timeBetweenEachSpawn + img->_lastFrame) {

		img->_fCol = (img->_fCol + 1) % img->_nCols; //Contempla el salto de linea
		if (img->_fCol == 0) //Al volver a la columna 0, cambia de fila
		{
			img->_fRow = (img->_fRow + 1) % img->_nRows; //Contempla el salto de columna
		}

		// Reinicia el contador
		img->_lastFrame = vt.currTime();
	}

	// --- RECTANGULO SOURCE: gestion de la propia textura (como avanza, como se muestra, como se renderiza)
	SDL_Rect src = build_sdlrect(
		img->_fCol * (img->_tex->width() / img->_nCols),	// posX * (anchura de cada fila).
		img->_fRow * (img->_tex->height() / img->_nRows),  // posY * (altura de cada fila).
		img->_tex->width() / img->_nCols,				// anchura textura / columnas.
		img->_tex->height() / img->_nRows				// altura textura / filas.
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
