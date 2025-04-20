#include "ImageWithFrames.h"

#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

ImageWithFrames::ImageWithFrames(Texture* tex, int startCol, int startRow, int frames) :
	_tex(tex), _lastFrame(0), _fCol(startCol), _fRow(startRow), _nFrames(frames) {
}

ImageWithFrames::ImageWithFrames(Texture* tex, int startCol, int startRow) :
	_tex(tex), _lastFrame(0), _fCol(startCol), _fRow(startRow), _nFrames(1) {
}

void ImageWithFrames::initComponent()
{
	ecs::Manager* mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}

