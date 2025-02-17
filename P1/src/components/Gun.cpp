#include "Gun.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
#include "Transform.h"

class Vector2D;

Gun::Gun(Transform* t) : _trPlayer(t)
{
}

Gun::~Gun()
{
}

//void Gun::initComponent()
//{
//	auto* mngr = _ent->getMngr();
//	//Recorremos el array de balas
//	for (Gun::Bullet& b : _bullets) {
//		
//	}
//}

void Gun::reset()
{
	//Recorremos el array de balas
	for (Gun::Bullet& b : _bullets) {
		//Las "desusamos"
		b.used = false;
	}
}

void Gun::render()
{
}

void Gun::update()
{
	auto& ihldr = ih();
	int bw = 5;
	int bh = 20;
	Vector2D c = _trPlayer->getPos() + Vector2D(_trPlayer->getWidth() / 2.0f, _trPlayer->getHeight() / 2.0f);
	Vector2D bp = c - Vector2D(bw / 2, _trPlayer->getHeight() / 2.0f + 5.0f + bh).rotate(_trPlayer->getRot()) - Vector2D(bw / 2, bh / 2);
	Vector2D bv = Vector2D(0, -1).rotate(_trPlayer->getRot()) * (_trPlayer->getVel().magnitude() + 5.0f);
	float br = Vector2D(0, -1).angle(bv);

	//Recorremos las balas
	for (Gun::Bullet& b : _bullets) {
		//Si se ha usado
		if (b.used) { 
			//Avanza pos + vel (en línea recta con la rotacion del shoot)
			b.pos->setX(b.pos->getX() + b.vel->getX());
			b.pos->setY(b.pos->getY() + b.vel->getY());
		}
	}

	//Si se pulsa S, dispara
	float timer = sdlutils().virtualTimer().currRealTime() / 100;
	if (ihldr.isKeyDown(SDL_SCANCODE_S) /*&& (float)(timer / 100) % 0.25f == 0 */ ) {
		shoot(&bp, &bv, bw, bh, br);
	}
	
}

void Gun::shoot(Vector2D* p, Vector2D* v, int width, int height, float r)
{
	int i = 0;
	while (i < _max_bullets && !_bullets[i].used)
	{
		i++;
	}


}
