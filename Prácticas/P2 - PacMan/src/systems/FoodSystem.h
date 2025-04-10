#pragma once
#include "../ecs/System.h"
#include "../game/Game.h"
#include "../sdlutils/SDLUtils.h"

class RandomNumberGenerator;

class FoodSystem : public ecs::System {
public:

    FoodSystem();
    virtual ~FoodSystem();
    void initSystem() override;
    void update() override;
    void recieve(const Message& m) override;
private:
    void generateFruitGrid();

    void onFruitEaten(ecs::entity_t e);
    //void checkNoFruit();
    //void generateGhostsByTime();

    unsigned int _lastFruitChanged;

    unsigned int _currNumOfFruit;

    bool _fruitType; // F -> normal; T -> milagroso (al crear la fruta)

    // random sdlutils generator.
    RandomNumberGenerator& _rand;

    const int MAX_FRUIT_NUMBER = 40; // luego cambiar.
};
