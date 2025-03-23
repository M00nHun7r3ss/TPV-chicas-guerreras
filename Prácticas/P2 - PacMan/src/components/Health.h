//#pragma once
//
//#include "../ecs/Component.h"
//
//class Texture;
//
//struct Health : public ecs::Component
//{
//public:
//
//	Health();
//	virtual ~Health();
//	void damage(int n);
//	void heal();
//
//	int getHealth() { return _currentHealth; }
//
//private:
//	int _currentHealth;
//	int _maxHealth;
//	Texture& _tex;
//};