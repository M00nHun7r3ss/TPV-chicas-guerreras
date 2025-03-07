#pragma once
#include "../ecs/Component.h"
#include <array>
#include "../utils/Vector2D.h"
#include <SDL.h>

class Vector2D;
class Transform;

class Gun : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::GUN)

	struct Bullet {
		bool used = false;
		Vector2D pos;
		Vector2D vel;
		int width;
		int height;
		float rot;

		// getters bala.
		inline Vector2D getBulletPos() const { return pos; }
		inline Vector2D getBulletVel() const { return vel; }
		inline int getBulletWidth() const { return width; }
		inline int getBulletHeight() const { return height; }
		inline float getBulletRot() const { return rot; }
		inline bool isBulletUsed() const { return used; }

		// setters bala.
		inline void setBulletPos(Vector2D position) { pos = position; }
		inline void setBulletVel(Vector2D velocity) { vel = velocity; }
		inline void setBulletWidth(int wid) { width = wid; }
		inline void setBulletHeight(int hei) { height = hei; }
		inline void setBulletRot(float rotation) { rot = rotation; }
		inline void setBulletUsed(bool u) { used = u; }
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
	void shoot(Vector2D p, Vector2D v, int width, int height, float r);
	bullets_array_t _bullets;
	Transform* _trPlayer;

	Uint32 _lastShoot;
};
