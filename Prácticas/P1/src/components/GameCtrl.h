// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"

class GameCtrl: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::GAMECTRL)

	GameCtrl();
	virtual ~GameCtrl();

	inline void onAsteroidDissappeared() {
		_currNumOfAsteroids--;
	}

	inline void onAsteroidDestroyed() {
		_currNumOfAsteroids--;
		_score++;
	}

	void initComponent() override;
	void update() override;
	void render() override;

private:
	void createAsteroid(unsigned int n);

	unsigned int _currNumOfAsteroids;
	unsigned int _score;
	unsigned int _asteroidsLimit;
};

