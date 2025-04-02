#include "ImageWithFrames.h"

#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

ImageWithFrames::ImageWithFrames(Texture* tex, int cols, int rows) :
	_tex(tex), _nCols(cols), _nRows(rows)
{
}

void ImageWithFrames::initComponent()
{
	ecs::Manager* mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

