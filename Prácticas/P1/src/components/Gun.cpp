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
	/*//Recorremos el array de balas
	for (Gun::Bullet& b : _bullets) {
		if (b.used) {
			SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(build_sdlcolor(0xffffffff)));
			SDL_Rect rect = { b.pos->getX(), b.pos->getY(), 5.0f, 5.0f };

		}
	}*/
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
			b.used = false;
		}
	}

	//Si se pulsa S, dispara
	//float timer = sdlutils().virtualTimer().currRealTime() / 100;
	
	// Inicialmente empieza en 0.25 segundos.
	float _timeBetweenEachSpawn = 250.0f;

	// Puede disparar en caso de apretar la tecla S.
	if (ihldr.isKeyDown(SDL_SCANCODE_S) && _timeBetweenEachSpawn == 250.0f) {
		shoot(&bp, &bv, bw, bh, br);

		// Va bajando el contador a 0.
		_timeBetweenEachSpawn--;

		// Si el tiempo entre un spawn y otro ha llegado a cero.
		if (_timeBetweenEachSpawn <= 0){
			_timeBetweenEachSpawn = 250.0f; // reinicia el contador.
		}
	}
	
	// SAMIR CLASE.
	/*
	if (_pos.getX() + _width < 0 || _pos.getX()> sdlutils().width() || _pos.getY() + _height < 0 || _pos.getX()> sdlutils().height()) {
		used = false
	}*/

	/*int i = (__lastUsed + 1) % _bullets.size();
	while (_bullest[i].used && i != _lastUsed) {
		i = (i + 1) % _bullets.size();
	}

	if (!_bullets[i].used) {
		_bullets[i].used = true;
		_bullets[i].pos = p;
		_bullets[i].vel = v;
	}*/
	
}

void Gun::shoot(Vector2D* p, Vector2D* v, int width, int height, float r)
{
	int i = 0;
	while (i < _max_bullets && !_bullets[i].used)
	{
		i++;
	}


}
