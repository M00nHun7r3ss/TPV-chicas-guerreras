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
	Uint32 _timeBetweenEachSpawn = 500;

	auto& vt = sdlutils().virtualTimer();

	if ( vt.currTime() > _timeBetweenEachSpawn + _lastFrame) {

		// Reinicia el contador
		_lastFrame = vt.currTime();

		// Va avanzando
		for (int i = 0; i < _nCols; i++)
		{
			_fCol = _fCol + 1 % _nCols; //Contempla el salto de linea
		}

	}

	//Renderizamos 
	//_tex->render();
	
}
