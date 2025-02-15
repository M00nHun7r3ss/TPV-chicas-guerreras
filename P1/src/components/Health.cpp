#include "Health.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
//#include "GameState.h"

Health::Health(){
}

Health::~Health(){
}

void Health::initComponent(){
	/*auto mngr = _ent->getMngr();
	_gameState = mngr->getComponent<GameState>(_ent);
	assert(_gameState != nullptr);*/
}

void Health::render(){
}
