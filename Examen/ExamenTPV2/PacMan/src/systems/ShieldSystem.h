#pragma once
#include "../ecs/System.h"
#include "../game/Game.h"

class ShieldSystem : public ecs::System {
public:

	ShieldSystem();
	virtual ~ShieldSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& m) override;

	bool isShieldOn() { return _isShieldOn; }

private:
	bool _isShieldOn;
	unsigned int _lastShieldStarted;

	float _N; //Numero de frutas que debe comer
	float _M; //Milisegundos en los que tiene que comerse la fruta
	float _X; //Espacio con respecto de pacman
	float _T; //Milisegundos de escudo activo
};

