#pragma once
#include "../ecs/Component.h"
#include <array>
#include <iterator>

class Vector2D;
class Transform;

class Gun : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::GUN)

	struct Bullet {
		bool used = false;
		Vector2D* pos;
		Vector2D* vel;
		int width;
		int height;
		float rot;

		// getters bala.
		inline int bulletWidth() const { return width; }
		inline int bulletHeight() const { return height; }
	};

	constexpr static uint8_t _max_bullets = 20;
	typedef std::array<Bullet, _max_bullets> bullets_array_t;
	typedef bullets_array_t::iterator iterator;

	Gun();
	Gun(Transform* t);
	virtual ~Gun();
	void reset();
	void render();
	void update();

	iterator begin() {
		return _bullets.begin();
	}
	iterator end() {
		return _bullets.end();
	}

private:
	void shoot(Vector2D* p, Vector2D* v, int width, int height, float r);
	bullets_array_t _bullets;
	Transform* _trPlayer;
};