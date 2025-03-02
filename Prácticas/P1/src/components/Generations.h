#pragma once

#include <SDL_stdinc.h>
#include "../ecs/Component.h"

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

private:

	Transform* _tr;
};

