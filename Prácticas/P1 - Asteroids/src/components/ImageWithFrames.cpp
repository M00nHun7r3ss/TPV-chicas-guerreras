#include "ImageWithFrames.h"

#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

ImageWithFrames::ImageWithFrames()
{
}

ImageWithFrames::ImageWithFrames(Texture* tex, int cols, int rows) :
_tex(tex), _nCols(cols), _nRows(rows)
{
}

ImageWithFrames::~ImageWithFrames()
{
}

void ImageWithFrames::initComponent()
{
	ecs::Manager* mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

void ImageWithFrames::render()
{
	// Inicialmente empieza en 0.5 segundos.
	Uint32 _timeBetweenEachSpawn = 50;

	VirtualTimer& vt = sdlutils().virtualTimer();

	//Gestion de frames
	if (vt.currTime() > _timeBetweenEachSpawn + _lastFrame) {

		_fCol = (_fCol + 1) % _nCols; //Contempla el salto de linea
		if (_fCol == 0) //Al volver a la columna 0, cambia de fila
		{
			_fRow = (_fRow + 1) % _nRows; //Contempla el salto de columna
		}

		// Reinicia el contador
		_lastFrame = vt.currTime();
	}

	// --- RECTANGULO SOURCE: gestion de la propia textura (como avanza, como se muestra, como se renderiza)
	SDL_Rect src = build_sdlrect(
		_fCol * (_tex->width() / _nCols),	// posX * (anchura de cada fila).
		_fRow * (_tex->height() / _nRows),  // posY * (altura de cada fila).
		_tex->width() / _nCols,				// anchura textura / columnas.
		_tex->height() / _nRows				// altura textura / filas.
	);

	// --- RECTANGULO DESTINO: rectangulo del asteroide ingame y ya.
	SDL_Rect dest = build_sdlrect(
		_tr->getPos().getX(),	    // pos x asteroide)
		_tr->getPos().getY(),		// pos y asteroide
		_tr->getWidth(),		    // en horizontal hay 6 frames.
		_tr->getHeight()		    // en vertical hay 5 frames.
	); 

	_tex->render(src, dest, _tr->getRot());
}
