#pragma once

#include <SDL_stdinc.h>

#include "../ecs/Component.h"
#include "../game/Game.h"

class Transform;
class Texture;

class ImageWithFrames : public ecs::Component
{
	
public:

	__CMPID_DECL__(ecs::cmp::IMAGEWITHFRAMES)

	ImageWithFrames();
	ImageWithFrames(Texture* tex, int cols, int rows);
	virtual ~ImageWithFrames();

	void setTexture(Texture* tex) {
		_tex = tex;
	}

	void initComponent() override;
	void render() override;

private:

	Transform* _tr;

	//Datos de textura general
	Texture* _tex;
	int _width;
	int _height;
	int _nCols;
	int _nRows;

	//Datos de asteroide
	int _aWidth;
	int _aHeight;
	int _aPosX;
	int _aPosY;

	//Cambio de frame
	Uint32 _lastFrame;
	int _fCol; //Column render in the frame
	int _fRow; //Row render in the frame

};




