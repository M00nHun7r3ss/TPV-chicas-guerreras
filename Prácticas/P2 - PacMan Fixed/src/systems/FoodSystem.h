#pragma once
#include "../ecs/System.h"
#include "../game/Game.h"

class FoodSystem : public ecs::System {
public:

	FoodSystem();
	virtual ~FoodSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& m) override;
private:
	void generateFruitGrid();
	void onGhostEaten(ecs::entity_t e);
	void removeAllGhosts();
	void generateGhostsByTime();

	unsigned int _ghostLimit;
	unsigned int _currNumOfGhosts;
	unsigned int _lastGhostAdded;

	const int MAX_FRUIT_NUMBER = 40; // luego cambiar.
	bool fruitType = false; // F -> normal; T -> milagroso
}; 