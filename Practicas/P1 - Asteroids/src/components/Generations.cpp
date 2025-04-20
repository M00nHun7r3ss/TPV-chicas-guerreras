#include "Generations.h"

#include "../sdlutils/SDLUtils.h"

Generations::Generations(){
}

Generations::~Generations(){
}

void Generations::generate(){
	RandomNumberGenerator& rand = sdlutils().rand(); // random number generator.

	// 0 -> SMALL, 1 -> MEDIUM, 2 -> BIG
	_generationLevel = rand.nextInt(0, 3);

	setGenerationSize(10.0f + 5.0f * (_generationLevel + 1)); // (lvl + 1) pa q no haga 0* algo
}
