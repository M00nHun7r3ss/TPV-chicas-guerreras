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
	//Recorremos el array de balas
	for (Gun::Bullet& b : _bullets) {
		if (b.used) {
			SDL_SetRenderDrawColor(sdlutils().renderer(), COLOREXP(build_sdlcolor(0xffffffff)));
			SDL_Rect rect = { b.pos->getX(), b.pos->getY(), 5.0f, 5.0f };

		}
	}
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

			//Si sale de pantalla, se desactiva
			if (b.pos->getX() + b.width < 0 || b.pos->getX()> sdlutils().width() ||
				b.pos->getY() + b.height < 0 || b.pos->getX()> sdlutils().height()) {
				b.used = false;
			}
		}
	}

	// Inicialmente empieza en 0.25 segundos.
	Uint32 _timeBetweenEachSpawn = 250;

	// Puede disparar en caso de apretar la tecla S.
	if (ihldr.isKeyDown(SDL_SCANCODE_S) && sdlutils().virtualTimer().currTime() - _timeBetweenEachSpawn > 250) {
		//Dispara
		shoot(&bp, &bv, bw, bh, br);

		// Reinicia el contador
		_timeBetweenEachSpawn = sdlutils().virtualTimer().currTime();
	}

}

void Gun::shoot(Vector2D* p, Vector2D* v, int width, int height, float r)
{

	//indice para la busqueda circular
	int _lastUsed = 0;
	//i no es 0 hasta que no llegue _lastUsed + 1 no llegue a 20. En otros casos, i = _lastUsed + 1
	int i = (_lastUsed + 1) % _bullets.size();
	//Si la bala está usada (ya se ha disparado), y no es la que acabamos de comprobar
	while (_bullets[i].used && i != _lastUsed) {
		//Avanza la busqueda, porque esa bala ya se ha disparado
		i = (i + 1) % _bullets.size();
	}

	//Si no se ha disparado ya
	if (!_bullets[i].used) {
		//La dispara en la posición y con la velocidad determinada
		_bullets[i].used = true;
		_bullets[i].pos = p;
		_bullets[i].vel = v;
	}
}
