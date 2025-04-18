#pragma once
#include "../ecs/System.h"

class ImmunitySystem : public ecs::System {
public:

	ImmunitySystem();
	virtual ~ImmunitySystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& m) override;

	bool isImmune() { return _isImmune; }

private:
	bool _isImmune;
	unsigned int _lastImmunityStarted;
};

