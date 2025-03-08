#pragma once

#include <SDL_stdinc.h>
#include "../ecs/Component.h"
#include "../game/Game.h"

class Transform;
class Generations : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::GENERATIONS)

	Generations();
	virtual ~Generations();

	void initComponent() override;
	void update() override{}
	void render() override{}
	void generate();

	// generation
	inline int getGenerationLevel() { return _generationLevel; }
	inline void setGenerationLevel(int l) { _generationLevel = l; }

	// width/height.
	inline int getGenerationSize() { return _gSize; }
	inline void setGenerationSize(float s) { _gSize = s; }


private:
	int _generationLevel;
	Transform* _tr;

	float _gSize;

};

