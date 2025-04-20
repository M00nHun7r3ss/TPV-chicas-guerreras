#pragma once

#include <SDL_stdinc.h>

#include "../ecs/Component.h"
#include "../game/Game.h"

class Transform;
class Texture;

struct ImageWithFrames : public ecs::Component
{

	ImageWithFrames() : _tex() {}
	ImageWithFrames(Texture* tex, int startCol, int startRow, int frames);
	ImageWithFrames(Texture* tex, int startCol, int startRow); //Frutas
	virtual ~ImageWithFrames() {}

	void initComponent() override;

	void setColRow(int col, int row) { _fCol = col; _fRow = row; }
	int getCol() { return _fCol; }
	int getRow() { return _fRow; }

	Transform* _tr;

	//Datos de textura (la unica que usamos: pacman_sprites)
	Texture* _tex;
	const int WIDTH = 1024;
	const int HEIGHT = 1024;
	const int COLS = 8;
	const int ROWS = 8;

	//Cambio de frame
	Uint32 _lastFrame;
	int _fCol; //Column render in the frame
	int _fRow; //Row render in the frame
	Uint32 _nFrames; // number of frames to render.

};


