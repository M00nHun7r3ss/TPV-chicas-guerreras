#pragma once

#include "../game/GameObject.h"
#include "PacmanState.h"

class Texture;
class PacmanWS : public GameObject {
public:
	enum State {
		WALKING, SPINNING, STILL
	};
	PacmanWS();
	virtual ~PacmanWS();
	void update() override;
	void render() override;
	void handleInput() override;
	void setImageRect(Texture* t, int rows, int cols, int row, int col);

	/*inline void setImg(Texture* img) {
		_img = img;
	}*/

	inline void setState(State s) {
		switch (s) {
		case SPINNING:
			_state = _spinning_state;
			break;
		case STILL:
			_state = _still_state;
			break;
		case WALKING:
			_state = _walking_state;
			break;
		default:
			assert(false);
			break;
		}
		_state->enter(*this);
	}
private:
	Texture* _img;
	SDL_Rect _src;

	PacmanState* _state;
	PacmanState* _spinning_state;
	PacmanState* _still_state;
	PacmanState* _walking_state;

};



