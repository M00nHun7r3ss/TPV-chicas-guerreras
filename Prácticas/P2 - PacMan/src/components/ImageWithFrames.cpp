#include "ImageWithFrames.h"

#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

ImageWithFrames::ImageWithFrames(Texture* tex, int startCol, int startRow, int frames) :
	_tex(tex), _fCol(startCol), _fRow(startRow), _nFrames(frames) {
}

void ImageWithFrames::initComponent()
{
	ecs::Manager* mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

