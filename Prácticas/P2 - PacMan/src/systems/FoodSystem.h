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
    //void onFruitEaten(ecs::entity_t e);
    //void checkNoFruit();
    //void generateGhostsByTime();

    unsigned int _currNumOfFruit;
    unsigned int _lastFruitAdded;
    bool _fruitType; // F -> normal; T -> milagroso

    const int MAX_FRUIT_NUMBER = 40; // luego cambiar.
};